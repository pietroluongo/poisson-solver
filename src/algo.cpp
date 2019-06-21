#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>


#define MAX_ITER 1000

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
    double q1 = x * (10-x);
    double q2 = y * (5-y);
    return (1.0/5.0) * (q1 + q2);
}

double efedexiseipsilom_contorno(double x, double y) {
    return 0.625*x*(10-x);
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
    printf("\nMAX ERRO: %lf\nComparing %lf and %lf, index %d (%d, %d)\n", max, ground[idx], vp[idx], idx, idx/11, idx%11);
    return max;
}

int main() {
    int nx = getNx();
    int ny = getNy();
    double w = getOmegaIdeal(nx, ny);
    printf("nx = %d ny = %d w = %lf\n\n", nx, ny, w);
    double a, b, c, d, e;
    a = b = (-1)/(hx*hx);
    c = d = (-1)/(hy*hy);
    e = 2 * ((1 / (hx*hx)) + (1/(hy*hy)));
    printf("a = %lf b = %lf c = %lf d = %lf e = %lf\n\n", a, b, c, d, e);
    int posAtual = 0;
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            fp[posAtual++] = efedexiseipsilom(i * hx, j * hy);
        }
    }
    // SOR
    int vecSize = nx*ny;
    for(int iter = 0; iter < MAX_ITER; iter++) {
        // 1ª iter
        vp[0] = (w/e) * (fp[0] - a * vp[1] - c * vp[nx]) + ((1-w) * vp[0]);
        for(int i = 1; i < vecSize-1; i++) {
            if(i < nx)
                vp[i] = (w/e) * (fp[i] - d * 0 - b * vp[i-1] - a * vp[i+1] - c * vp[i+nx]) + ((1-w) * vp[i]);
            else if(i+nx > vecSize)
                vp[i] = (w/e) * (fp[i] - d * vp[i-nx] - b*vp[i-1] - a * vp[i+1]) + (1-w) * vp[i]; 
            else
                vp[i] = (w/e) * (fp[i] - d * vp[i-nx] - b*vp[i-1] - a * vp[i+1] - c * vp[i+nx]) + (1-w) * vp[i];
        }
        // Última iter
        vp[vecSize-1] = (w/e) * (fp[vecSize-1] - d * vp[vecSize-1-nx] - b * vp[vecSize-1-1]) + (1-w) * vp[vecSize-1];
    }

    // Casos de contorno
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            if(i * hy == 2.5) {
                vp[i*ny + j] = efedexiseipsilom_contorno(i*hx, j*hy);
            }
            if(i == 0 || j == 0 || j == ny-1 || i == nx-1)
                vp[i*ny + j] = 0;
        }
    }
    
    printf("\nVP:\n");
    for(int i = 0; i < nx; i++) {
        printf("%3lf -> ", i * hy);
        for(int j = 0; j < ny; j++) {
            printf("%3lf ", vp[i * ny + j]);
        }
        printf("\n");
    }

    posAtual = 0;
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            ground[posAtual++] = vedexisipsilon(i * hx, j * hy);
        }
    }

    printf("\nExata:\n");
    for(int i = 0; i < nx; i++) {
        printf("%3lf -> ", i * hy);
        for(int j = 0; j < ny; j++) {
            printf("%3lf ", ground[i * ny + j]);
        }
        printf("\n");
    }

    printf("\nDiferencial:\n");
    for(int i = 0; i < nx; i++) {
        printf("%3lf -> ", i * hy);
        for(int j = 0; j < ny; j++) {
            printf("%3lf ", ground[i * ny + j] - vp[i * ny + j]);
        }
        printf("\n");
    }



    //printStuff();
    //writeOutputToFile();
    getErro();
    return 0;
}