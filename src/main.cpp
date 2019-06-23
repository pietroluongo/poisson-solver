#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "poissonSOR.h"

double efedexiseipsilom(double x, double y) {
    return ((x * (10-x)) + (y * (5-y)))/5.0;
}

double efedexiseipsilom_contorno(double x, double y) {
    return (0.625)*x*(10-x);
}

double vedexisipsilon(double x, double y) {
    return (x*(10-x) * y * (5-y))/10;
}


int main() {
    FILE* f;
    f = fopen("log.txt", "w");
    poissonSOR dados = poissonSOR(0, 10, 0, 5, 0.5, 0.5);
    dados.setFXY(efedexiseipsilom);
    dados.setType(VALIDACAO);
    dados.setValFunc(vedexisipsilon);
    dados.addContorno(efedexiseipsilom_contorno);
    dados.process();
    fprintf(f, "Processado validacao hx = 0.5, hy = 0.5, erro = %.15lf\n", dados.getErro());
    dados.writeOutputData();
    dados.resize(0.25,0.25);
    dados.process(); 
    fprintf(f, "Processado validacao hx = 0.25, hy = 0.25, erro = %.15lf\n", dados.getErro());
    dados.writeOutputData();
    dados.resize(0.125, 0.125);
    dados.process();
    fprintf(f, "Processado validacao hx = 0.125, hy = 0.125, erro = %.15lf\n", dados.getErro());
    dados.writeOutputData();
    //dados.debug();
    return 0;
}