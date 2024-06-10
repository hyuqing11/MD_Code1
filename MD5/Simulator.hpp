
#ifndef Simulator_hpp
#define Simulator_hpp

#include <stdio.h>
#include "ReadInput.hpp"
#include <cmath>
#include "RealVec.hpp"

class Simulator{
private:
    int datVarsCopied, datVarsInit, x0Init;
    RealVec gap, base;
public:
    //Simulation *nmSimu;
    double *x, *v, *a, *m;
    int *atomType, unitCell[3];
    int nAtom, nTypes, dim,nebrNow;
    double dispHi;
    RealVec reg;
    double temp, mass, delta_t,density;
    //Simulator(double dt, int nAtom, int nTypes);
    void ComputeUniteCell();
    void run();
    Simulator(ReadInput &rInp);
    void Initialization();
    void InitialVelocity();
    void InitialAcceleration();
    void InitialPosition();
    void calculateVCM();
    ~Simulator();
    double gasdev();
    void CopyDataVars(double *x, double *v, double *a, int *atomType, double *m);
    void CopyDataVars();
};

#endif /* Simulator_hpp */
