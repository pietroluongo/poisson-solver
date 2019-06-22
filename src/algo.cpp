#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>


#define MAX_ITER 10000

using namespace std;

// Domínio
int dom_x0 = 0;
int dom_y0 = 0;
int dom_x1 = 10;
int dom_y1 = 5;

double hx = 0.5;
double hy = 0.5;

// fp tem tamanho nx * ny
double fp[21*11];
double vp[21*11] = {};

double ground[21*11];

int nx, ny;

int getNx() {
    return 1 + (abs(dom_x1 - dom_x0) / hx);
}

int getNy() {
    return 1 + (abs(dom_y1 - dom_y0) / hy);
}

double getOmegaIdeal(int nx, int ny) {
    double t = cos(M_PI/nx) + cos(M_PI/ny);
    double t2 = t*t;
    return ((8 - (sqrt(64-16*t2)))/t2);
}

double efedexiseipsilom(double x, double y) {
    return ((x * (10-x)) + (y * (5-y)))/5.0;
}

double efedexiseipsilom_contorno(double x, double y) {
    //printf("\nContornando com x = %lf\n", x);
    return (0.625)*x*(10-x);
}

double vedexisipsilon(double x, double y) {
    return (x*(10-x) * y * (5-y))/10;
}

void writeOutputToFile() {
    FILE* f;
    f = fopen("teste.txt", "w");
    for(int i = 0; i < 21*11; i++) {
        fprintf(f, "%lf\n",vp[i]);
    }
    fclose(f);
    f = fopen("ground.txt", "w");
    for(int i = 0; i < 21*11; i++) {
        fprintf(f, "%lf\n", ground[i]);
    }
    fclose(f);
}

void printStuff() {
    printf("f = \n\n");
    for(int i = 0; i <= 10; i++) {
        printf("y = %.2lf -> ", i*hy);
        for(int j = 0; j <= 5; j++) {
            // Condições de contorno
            if((j * hy) == 2.5) {
                printf("%.4lf ", efedexiseipsilom_contorno(i, j));
            }
            else if (j == 0 || j == 5 || i == 0 || i == 10) {
                printf("%.4lf ", 0.0);
            }
            else
                printf("%.4lf ", efedexiseipsilom(i, j));
        }
        printf("\n");
    }
    printf("\nV = \n\n");
    for(int i = 0; i <= 10; i++) {
        printf("y = %.2lf -> ", (i*hy));
        for(int j = 0; j <= 5; j++) {
            printf("%.4lf ", vedexisipsilon(i, j));
        }
        printf("\n");
    }
    printf("\nfp:\n");
    for(int i = 0; i < 21*11; i++) {
        printf("%3d - [%lf]\n", i, fp[i]);
    }
    printf("\n");

    printf("\nvp:\n");
    for(int i = 0; i < 21*11; i++) {
        printf("%3d - [%lf]\n", i, vp[i]);
    }
    printf("\n");
}

double getErro() {
    double max = -1.0;
    int idx = -1;
    for(int i = 0; i < 21*11; i++) {
        double diff = abs(ground[i]-vp[i]);
        if(diff > max) {
            max = diff;
            idx = i;
        }
    }
    printf("\nMAX ERRO: %.32lf\nComparing %lf and %lf, index %d (%d, %d)\n", max, ground[idx], vp[idx], idx, idx/11, idx%11);
    return max;
}

void debug() {
    printf("matriz fp (%dx%d)\n", ny, nx);

    for(int i = 0; i < nx*ny; i++) {
        if(i % nx == 0)
            printf("\n");
        printf("%08.5lf ", fp[i]);
    }

    printf("\n\nmatriz ground (%dx%d)\n", ny, nx);

    for(int i = 0; i < nx*ny; i++) {
        if(i % nx == 0)
            printf("\n");
        printf("%08.5lf ", ground[i]);
    }

    printf("\n\nmatriz vp (%dx%d)\n", ny, nx);

    for(int i = 0; i < nx*ny; i++) {
        if(i % nx == 0)
            printf("\n");
        printf("%08.5lf ", vp[i]);
    }
    cout << endl;

    printf("\nDiferencial\n");
    for(int i = 0; i < nx*ny; i++) {
        if(i%21 == 0)
            printf("\n");
        printf("%08.5lf ", ground[i] - vp[i]);
    }
    cout << endl;
    return;
}

int main() {
    nx = getNx(); // 21
    ny = getNy(); // 11
    double w = getOmegaIdeal(nx, ny);
    printf("nx = %d ny = %d w = %lf niter = %d\n\n", nx, ny, w, MAX_ITER);
    double a, b, c, d, e;
    a = b = (-1.)/(hx*hx);
    c = d = (-1.)/(hy*hy);
    e = 2. * ((1. / (hx*hx)) + (1./(hy*hy)));
    printf("a = %lf b = %lf c = %lf d = %lf e = %lf\n\n", a, b, c, d, e);

    int a0 = a;
    int b0 = b;
    int c0 = c;
    int d0 = d;
    int e0 = e;

    // Normal order
    // for(int i = 0; i < ny; i++) {
    //     for(int j = 0; j < nx; j++) {

    //     }
    // }

    // Column Major - FP - OK!
    for(int j = 0; j < nx; j++) {
        for(int i = 0; i < ny; i++) {
            fp[nx*i + j] = efedexiseipsilom(j * hx, i * hy);
        }
    }

    // Casos de contorno no Fp
    for(int j = 0; j < nx; j++) {
        for(int i = 0; i < ny; i++) {
            if(i * hy == 2.5)
                fp[nx * i + j] = efedexiseipsilom_contorno(j * hx, i * hy);
            if(i == 0 || j == 0 || j == nx-1 || i == ny-1)
                fp[nx * i + j] = 0;
        }
    }

    // Column Major - Ground - OK!
    for(int j = 0; j < nx; j++) {
        for(int i = 0; i < ny; i++) {
            ground[nx*i + j] = vedexisipsilon(j * hx, i * hy);
        }
    }

    // SOR
    int vecSize = nx*ny;
    for(int iter = 0; iter < MAX_ITER; iter++) {
        // 1ª iter
        //vp[0] = (w/e) * (fp[0] - a * vp[1] - c * vp[nx]) + ((1-w) * vp[0]);
        vp[0] = 0;
        for(int i = 1; i < vecSize-1; i++) {
            // Contornos
            if(i % nx == 0 || i % (nx) == (nx-1) || i<nx || (ny-1) * nx < i) {
                vp[i] = 0;
                continue;
            }
            if((i / 21 ) * 0.5 == 2.5) {
                vp[i] = fp[i];
                continue;
            }
            if(i < nx)
                vp[i] = (w/e) * (fp[i] - d * 0 - b * vp[i-1] - a * vp[i+1] - c * vp[i+nx]) + ((1-w) * vp[i]);
            else if(i+nx > vecSize)
                vp[i] = (w/e) * (fp[i] - d * vp[i-nx] - b*vp[i-1] - a * vp[i+1]) + (1-w) * vp[i]; 
            else
                vp[i] = (w/e) * (fp[i] - d * vp[i-nx] - b*vp[i-1] - a * vp[i+1] - c * vp[i+nx]) + (1-w) * vp[i];
        }
        // Última iter
        vp[vecSize-1] = 0;
        //vp[vecSize-1] = (w/e) * (fp[vecSize-1] - d * vp[vecSize-1-nx] - b * vp[vecSize-1-1]) + (1-w) * vp[vecSize-1];
    }

    // int vecSize = nx*ny;
    // for(int iter = 0; iter < MAX_ITER; iter++) {
    //     for(int i = 1; i <= vecSize; i++) {
    //         a = a0;
    //         b = b0;
    //         c = c0;
    //         d = d0;
    //         int it = i-1;
    //         // Condições de contorno
    //         if((it / 11) * 0.5 == 2.5)
    //             vp[it] = w * fp[it] + (1-w)* vp[it];
    //         // Fronteira
    //         if(it % nx == 0 || it % (nx) == (nx-1) || it<nx || (ny-1) * nx <i) {
    //             vp[it] = w * fp[it] + (1-w)* vp[it];
    //         }

    //         if(it-nx)

    //         if(i%nx == 1)
    //             b = 0;
    //         if(i < nx)
    //             d = 0;
    //         if(i%nx == 0)
    //             a = 0;
    //         if((ny-1)*nx < i)
    //             c = 0;
    //         vp[it] = (w/e) * (fp[it] - d * vp[it-nx] - b*vp[it-1] - a * vp[it+1] - c * vp[it+nx]) + ((1-w) * vp[it]);
    //     }
    // }

    // Casos de contorno - OK!
    // for(int j = 0; j < nx; j++) {
    //     for(int i = 0; i < ny; i++) {
    //         if(i * hy == 2.5)
    //             vp[nx * i + j] = efedexiseipsilom_contorno(j * hx, i * hy);
    //         if(i == 0 || j == 0 || j == nx-1 || i == ny-1)
    //             vp[nx * i + j] = 0;
    //     }
    // }
    debug();
    getErro();
    writeOutputToFile();
    return 0;
}