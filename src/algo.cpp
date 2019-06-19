#include <cstdio>
#include <cstdlib>
#include <cmath>

// Domínio
int dom_x0 = 0;
int dom_y0 = 0;
int dom_x1 = 10;
int dom_y1 = 5;

double hx = 0.5;
double hy = 0.5;

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

double vedexisipsilon(double x, double y) {
    return (x*(10-x) * y * (5-y))/10;
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
    printf("f = \n\n");
    for(int i = 0; i <= 10; i++) {
        printf("y = %.2lf -> ", i*hy);
        for(int j = 0; j <= 5; j++) {
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
    return 0;
}