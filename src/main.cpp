#include <cstdio>
#include <cstdlib>
#include <cmath>

#define VALIDACAO
// #define CAPACITORES


// Se estamos testando o primeiro caso (o de validação do sistema)
#ifdef VALIDACAO
// FIXME - Definir esses valores de acordo com o pdf
#define NX 5
#define NY 4
#endif

// Se estamos testando o segundo caso (o de capacitores)
#ifdef CAPACITORES

#define NX 5
#define NY 4

#endif

// Struct contendo as constantes do método SOR
struct consts {
    double a, b, c, d, e;
};

// Struct que representa o domínio da função
struct dom {
    int x0, y0, x1, y1;
};

// Struct que representa as informações do sistema
struct poissonSOR {
    // Domínio do problema
    dom dominio;
    
    // Constantes do SOR
    consts cts;
    
    // nx e ny, valores em x e em y
    int nx;
    int ny;

    double omega;
};

// Calcula o ômega ideal de acordo com a equação para o método SOR
double getOmegaIdeal(int nx, int ny) {
    double t = cos(M_PI/nx) + cos(M_PI/ny);
    double t2 = t*t;
    return (8 - sqrt(64-16*t2)/t2);
}

// Seta o valor das constantes usadas no método SOR
void setConstants(consts& cts) {
    // a = b = -1/h²x
    // c = d = -1/h²y
    // e = -2(1/h²x + 1/h²y)
    return; 
}

// Inicializa um dominio
dom initDominio(int a, int b, int c, int d, dom& dominio) {
    dominio.x0 = a;
    dominio.y0 = b;
    dominio.x1 = c;
    dominio.y1 = d;
    return dominio;
}

int main() {
    poissonSOR dados;
    // Inicialização do domínio
    initDominio(0, 10, 0, 5, dados.dominio);
    
    // Definição de nx e ny
    dados.nx = NX;
    dados.ny = NY;

    // Cálculo do w ideal
    dados.omega = getOmegaIdeal(dados.nx, dados.ny);

    // Inicialização das constantes
    setConstants(dados.cts);
    
    return 0;
}