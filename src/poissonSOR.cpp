#include "poissonSOR.h"

double getOmegaIdeal(int nx, int ny);

struct Dominio {
    int x0, y0, x1, y1;
    Dominio(int a, int b, int c, int d) {
        x0 = a;
        y0 = b;
        x1 = c;
        y1 = d;
    }
};

poissonSOR::poissonSOR(int x0, int x1, int y0, int y1, double hx, double hy) {
    this->w = getOmegaIdeal(nx, ny);
    this->hx = hx;
    this->hy = hy;
    this->dom = new Dominio(x0, y0, x1, y1);
    this->nx = 1 + (abs(dom->x1 - dom->x0) / this->hx);
    this->ny = 1 + (abs(dom->y1 - dom->y0) / this->hy);
    this->a = this->b = (-1.)/(hx*hx);
    this->c = this->d = (-1.)/(hy*hy);
    this->e = 2. * ((1. / (hx*hx)) + (1./(hy*hy)));
    t = NIL;
    return;
}

poissonSOR::~poissonSOR() {
    delete(this->dom);
    return;
}

void poissonSOR::setType(type t) {
    this->t = t;
    return;
}

void poissonSOR::setFXY(double (*fxy) (double, double)) {
    this->aproxFunc = fxy;
    return;
}

void poissonSOR::calcFp() {
    for(int j = 0; j < nx; j++) {
        for(int i = 0; i < ny; i++) {
            this->fp[nx*i + j] = this->aproxFunc(j * hx, i * hy);
        }
    }
    checkContornos();
    return;
}

// Essa função meio que fica "hardcoded" aqui mesmo
void poissonSOR::checkContornos() {
    switch(this->t) {
        case NIL:
            printf("ERRO: O tipo de contorno não foi configurado!");
            break;
        case VALIDACAO:
            // Casos de contorno no Fp
            for(int j = 0; j < nx; j++) {
                for(int i = 0; i < ny; i++) {
                    if(i * hy == 2.5)
                        fp[nx * i + j] = this->contornos[0](j * hx, i * hy);
                    if(i == 0 || j == 0 || j == nx-1 || i == ny-1)
                        fp[nx * i + j] = 0;
                }
            }
            break;
        case CAPACITORES:
            break;
    }
    return;
}

void poissonSOR::addContorno(double (*f) (double, double)) {
    this->contornos.push_back(f);
    return;
}

void poissonSOR::process() {
    this->calcFp();
}

void poissonSOR::setValFunc(double (*f) (double, double)) {
    this->grndFunc = f;
    return;
}

void poissonSOR::debug() {
    printf("\n\nOBJ DEBUG STUFF BELOW!\n\n");
    printf("a = %d, b = %d, c = %d, d = %d, e = %d\n", this->a, this->b, this->c, this->d, this->e);
    printf("hx = %.4lf hy = %.4lf nx = %d ny = %d\n", this->hx, this->hy, this->nx, this->ny);
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
    printf("\n");

    printf("\nDiferencial\n");
    for(int i = 0; i < nx*ny; i++) {
        if(i%nx == 0)
            printf("\n");
        printf("%08.5lf ", ground[i] - vp[i]);
    }
    printf("\n");
    return;
}

// Calcula o ômega ideal de acordo com a equação para o método SOR
double getOmegaIdeal(int nx, int ny) {
    double t = cos(M_PI/nx) + cos(M_PI/ny);
    double t2 = t*t;
    return (8 - sqrt(64-16*t2)/t2);
}