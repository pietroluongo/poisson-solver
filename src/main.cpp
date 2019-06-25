#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "poissonSOR.h"

double fxy(double x, double y) {
    return ((x * (10-x)) + (y * (5-y)))/5.0;
}

double fxy_contorno(double x, double y) {
    return (0.625)*x*(10-x);
}

double vxy(double x, double y) {
    return (x*(10-x) * y * (5-y))/10;
}

double fxy_capacitor(double x, double y) {
    return 0;
}

int main() {
    FILE* f;
    f = fopen("log.txt", "w");
    poissonSOR dados = poissonSOR(0, 10, 0, 5, 0.5, 0.5);
    dados.setFXY(fxy);
    dados.setType(VALIDACAO);
    dados.setValFunc(vxy);
    dados.addContorno(fxy_contorno);
    // dados.process();
    // fprintf(f, "Processado validacao hx = 0.5, hy = 0.5, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getErro(), dados.getErroEle());
    // dados.writeOutputData();
    for(int i = 0; i < 100; i += 10) {
        if(i == 0)
            dados.setMaxIter(i+1);
        else
            dados.setMaxIter(i);
        dados.process();
        fprintf(f, "Processado validacao hx = 0.5, hy = 0.5, nIter = %d, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getMaxIter(), dados.getErro(), dados.getErroEle());

    }



    dados.resize(0.25,0.25);
    // dados.process();
    // fprintf(f, "Processado validacao hx = 0.25, hy = 0.25, nIter = %d, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getMaxIter(), dados.getErro(), dados.getErroEle());
    // dados.writeOutputData();
    for(int i = 0; i < 100; i += 10) {
        if(i == 0)
            dados.setMaxIter(i+1);
        else
            dados.setMaxIter(i);
        dados.process();
        fprintf(f, "Processado validacao hx = 0.25, hy = 0.25, nIter = %d, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getMaxIter(), dados.getErro(), dados.getErroEle());

    }




    dados.resize(0.125, 0.125);
    // dados.process();
    // fprintf(f, "Processado validacao hx = 0.125, hy = 0.125, nIter = %d, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getMaxIter(), dados.getErro(), dados.getErroEle());
    // dados.writeOutputData();

    for(int i = 0; i < 100; i += 10) {
        if(i == 0)
            dados.setMaxIter(i+1);
        else
            dados.setMaxIter(i);
        dados.process();
        fprintf(f, "Processado validacao hx = 0.125, hy = 0.125, nIter = %d, erro = %.15lf, erro campo eletrico = %.15lf\n", dados.getMaxIter(), dados.getErro(), dados.getErroEle());

    }

    // dados = poissonSOR(0, 10, 0, 5, 0.5, 0.5);
    // dados.setFXY(fxy_capacitor);
    // dados.setType(CAPACITORES);
    // dados.process();
    // fprintf(f, "Processado capacitores hx = 0.5, hy = 0.5\n");
    // dados.writeOutputData();
    // dados.resize(0.25, 0.25);
    // dados.process();
    // fprintf(f, "Processado capacitores hx = 0.25, hy = 0.25\n");
    // dados.writeOutputData();
    // dados.resize(0.125, 0.125);
    // dados.process();
    // fprintf(f, "Processado capacitores hx = 0.125, hy = 0.125\n");    
    // dados.writeOutputData();
    // fclose(f);
    return 0;
}