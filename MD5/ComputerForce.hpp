
#ifndef ComputeForce_hpp
#define ComputeForce_hpp
#include <stdio.h>
#include <vector>
#include <array>
#include "RealVec.hpp"
#include <cmath>
#include "Simulator.hpp"
#include "IntVec.hpp"
class ComputerForce{
    
private:
    static constexpr int N_OFFSET = 14;
    static const std::array<std::array<int, 3>, N_OFFSET> OFFSET_VALS;
    double rrCutOff, rCutOff, rr, r2Inv, r6Inv;
    int nbrtabLen, *nbrTab, nbrNow, nbrtabMax, nbrtabFac, rNebrShell;
    int *cellList;
    RealVec dr, invWid, rs, shift;
    IntVec cells;
    double rrNebr;
    int n, m1, m2,c;
    IntVec cc, m1v, m2v;
    
public:
    double *x, *a, *v;
    int dim, nAtom, unitCell[3];
    RealVec reg;
    double f, uSum, virSum;
    ComputerForce(Simulator &nmD1);
    ~ComputerForce();
    void Initialization();
    void computer_force();
    void BuildNebrList();
    void ApplyBoundaryCondition(IntVec &vec);
    double ApplyBoundaryCondition(double x, int dimId);
};
#endif /* ComputeForce_hpp */
