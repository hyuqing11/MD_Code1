

#ifndef IntVec_hpp
#define IntVec_hpp
#include <iostream>
//#include "RealVec.hpp"

#include <cmath>
class IntVec{
private:
    int dim;
public:
    int *val;
    
    IntVec();
    IntVec(int n);
    ~IntVec();
    double Mag();
    int GetDim() const;
    int VProd();
    void SetDim(int n);
    int VLinear(IntVec &v);
    void Add(IntVec &v);
    void Sub(IntVec &v);
    
    void SetVal(int r);
    void Zero();

    void Add(int r);
    void Sub(int r);
    void Mul(int r);
    void Div(int r);
    //RealVec Div(RealVec &v);
    void SetVal(int x, int y, int z);
};
    

#endif /* IntVec_hpp */
