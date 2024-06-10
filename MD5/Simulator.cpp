
#include "Simulator.hpp"
#include <cstdlib>
Simulator::Simulator(ReadInput &rInp){
    nAtom = rInp.GetNAtomsSA();
    nTypes = rInp.GetNTypesSA();
    dim = rInp.GetDim();
    mass = rInp.GetMassSA(0);
    temp = rInp.Gettemp();
    datVarsCopied = 0;
    datVarsInit = 0;
    x0Init = 0;
    delta_t = rInp.GetdtSA();
    x = NULL;
    v = NULL;
    a = NULL;
    m = NULL;
    atomType = NULL;
    //nmSimu = new Simulation;
    x = new double[dim * nAtom];
    v = new double[dim * nAtom];
    a = new double[dim * nAtom];
    for (int i = 0; i < dim; i++){
        unitCell[i] = 0;
    }
    reg.SetDim(dim);
    gap.SetDim(dim);
    base.SetDim(dim);
    nebrNow = 0;
    dispHi = 0.;
    density= rInp.Getdensity();
   
    //nmSimu->CopyDataVars(x, v, a, atomType, m);
}

void Simulator::Initialization(){
    InitialPosition();
    InitialVelocity();
    InitialAcceleration();
    
}
void Simulator::InitialPosition(){
    ComputeUniteCell();
    for (int i = 0; i < dim; i++ ){
        gap.val[i] = reg.val[i] / unitCell[i];
    }
    int n = 0;
    for (int nz = 0; nz < unitCell[2]; ++nz){
        for (int ny = 0; ny < unitCell[1]; ++ny){
            for (int nx = 0; nx < unitCell[0]; ++nx){
                base.val[0] = (nx + 0.25) * gap.val[0] - 0.5 *reg.val[0];
                base.val[1] = (ny + 0.25) * gap.val[1] - 0.5 *reg.val[1];
                base.val[2] = (nz + 0.25) * gap.val[2] - 0.5 *reg.val[2];
                for (int m =0; m<4; ++m){
                    x[3 * n] = base.val[0];
                    x[3 * n + 1] = base.val[1];
                    x[3 * n + 2] = base.val[2];
                    if (m !=3){
                        if (m!=0) x[3 * n] += 0.5 * gap.val[0];
                        if (m!=1) x[3 * n + 1] += 0.5 * gap.val[1];
                        if (m!=2) x[3 * n + 2] += 0.5 * gap.val[2];
                    }
                    ++n;
                }
            }
        }
    }
    
}
void Simulator::ComputeUniteCell(){
    int M=1;
    double volume = 1.0 /std::pow(density/4.0, 1.0/3.0);
    while (4 * M * M * M < nAtom){
        ++M;
    }
    
    for (int i = 0; i < 3; i++){
        unitCell[i] = M;
        reg.val[i] = volume * M;
    }
}

void Simulator::InitialVelocity(){
    double vMag = sqrt(3 * nAtom-1) * temp;
    for (int n = 0; n < nAtom; ++n) {
        v[3 * n] = gasdev()/vMag;
        v[3 * n + 1] = gasdev()/vMag;
        v[3 * n + 2] = gasdev()/vMag;
    }
}

void Simulator::calculateVCM(){
    double vCM[3] = {0, 0, 0};
    for (int n = 0; n < nAtom; ++n) {
        vCM[0] += v[dim * n] * mass;
        vCM[1] += v[dim * n + 1] * mass;
        vCM[2] += v[dim * n + 2] * mass;
    }
    for (int i = 0; i < 3; ++i) {
        vCM[i] = vCM[i]/mass;
    }
}
void Simulator::InitialAcceleration(){
    for (int n = 0; n < nAtom; n++){
        a[3 * n] = 0.0;
        a[3 * n + 1] = 0.0;
        a[3 * n + 2] = 0.0;
    }
}

Simulator::~Simulator()
{
    delete [] x;
    delete [] v;
    delete [] a;
    delete [] m;
    
}

double Simulator::gasdev(){
    static int available = 0;
       static double gset;
       double fac, r_sq, v1, v2;
       if (!available) {
           do {
               v1 = 2.0 * rand() / RAND_MAX - 1;
               v2 = 2.0 * rand() / RAND_MAX - 1;
               r_sq = v1 * v1 + v2 * v2;
           } while (r_sq >= 1 || r_sq == 0);
           fac = sqrt(-2.0 * log(r_sq) / r_sq);
           gset = v1 * fac;
           available = 1;
           return v2 * fac;
       } else {
           available = 0;
           return gset;
       }
   }

void Simulator::run(){
    
}

void Simulator::CopyDataVars(double *x, double *v, double *a, int *atomType, double *m)
{    if(datVarsCopied == 1)
    {    printf("Data varriables for normal mode simulaiton driver data variables cannot be reinitiallized\n");
        exit(0);
    }

    datVarsCopied = 1;
    datVarsInit = 0;

    this->x = x;
    this->v = v;
    this->a = a;
    this->atomType = atomType;
    this->m = m;
    
}
void Simulator::CopyDataVars()
{    if(datVarsCopied == 1)
    {    printf("Data varriables for normal mode simulaiton driver data variables cannot be reinitiallized\n");
        exit(0);
    }
    double dim = 3;
    datVarsCopied = 1;
    datVarsInit = 1;
    x = new double[dim * nAtom];
    v = new double[dim * nAtom];
    a = new double[dim * nAtom];

    atomType = new int[nAtom];
    m = new double[nTypes];
    //nmSimu->CopyDataVars(x, v, a, atomType, m);
}


