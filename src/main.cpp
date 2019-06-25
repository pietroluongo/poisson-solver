#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "poissonSOR.h"

FILE* logFile;

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

void generateLatexTableOutput(poissonSOR& p, FILE* f) {
    for(int i = 0; i <= 150; i += 15) {
        p.reset();
        if(i == 0)
            p.setMaxIter(i+1);
        else
            p.setMaxIter(i);
        p.process();
        fprintf(f, "%d & %.12lf & %.12lf \\\\\n", p.getMaxIter(), p.getErro(), p.getErroEle());
    }
}

void log_process(double p, poissonSOR& d) {
    fprintf(logFile, "Processado validacao hx = %.4lf, hy = %.4lf, erro = %.15lf, erro campo eletrico = %.15lf\n", p, p, d.getErro(), d.getErroEle());

}

int main() {
    logFile = fopen("log.txt", "w");
    poissonSOR dados = poissonSOR(0, 10, 0, 5, 0.5, 0.5);
    dados.setFXY(fxy);
    dados.setType(VALIDACAO);
    dados.setValFunc(vxy);
    dados.addContorno(fxy_contorno);
    dados.setMaxIter(400);
    dados.process();
    log_process(0.5, dados);
    dados.writeOutputData();    
    dados.resize(0.25, 0.25);
    dados.process();
    log_process(0.25, dados);
    dados.writeOutputData();
    dados.resize(0.125, 0.125);
    dados.process();
    log_process(0.125, dados);
    dados.writeOutputData();
    dados = poissonSOR(0, 10, 0, 5, 0.5, 0.5);
    dados.setFXY(fxy_capacitor);
    dados.setType(CAPACITORES);
    dados.process();
    fprintf(logFile, "Processado capacitores hx = 0.5, hy = 0.5\n");
    dados.writeOutputData();
    dados.resize(0.25, 0.25);
    dados.process();
    fprintf(logFile, "Processado capacitores hx = 0.25, hy = 0.25\n");
    dados.writeOutputData();
    dados.resize(0.125, 0.125);
    dados.process();
    fprintf(logFile, "Processado capacitores hx = 0.125, hy = 0.125\n");    
    dados.writeOutputData();
    fclose(logFile);
    return 0;
}