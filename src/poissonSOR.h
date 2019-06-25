#include <cmath>
#include <cstdio>
#include <vector>
#include <string>

#define MAX_SIZE 10000
#define MAX_ITER 300

typedef struct Dominio dominio;

enum type {
    NIL,
    VALIDACAO,
    CAPACITORES
};

class poissonSOR {
private:
    dominio* dom;
    int a, b, c, d, e;
    int nx, ny;
    double w;
    double fp[MAX_SIZE] = {};
    double vp[MAX_SIZE] = {};
    double ground[MAX_SIZE] = {};
    double ground_ep[MAX_SIZE] = {};
    double ep[MAX_SIZE] = {};
    double hx, hy;
    double (*aproxFunc)(double, double);
    double (*grndFunc) (double, double);
    std::vector<double (*) (double, double)> contornos;
    type t;
    int vecSize;
    double erro_vp;
    double erro_ele;
public:
    poissonSOR(int x0, int x1, int y0, int y1, double hx, double hy);
    ~poissonSOR();
    void setType(type t);
    void addContorno(double (*f) (double, double));
    void setFXY(double (*fxy) (double, double));
    void setValFunc(double (*f) (double, double));
    void debug();
    void process();
    void resize(double hx, double hy);
    void writeOutputData();
    double getErro() { return this->erro_vp; };
    double getErroEle() { return this->erro_ele; };
private:
    void calcFp();
    void checkContornos();
    void calcExact();
    void doSOR();
    void calcErr();
    void calcCampElet();
    void calcCampElet_e();
    void calcErrEle();
};