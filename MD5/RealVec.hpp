
#ifndef RealVec_hpp
#define RealVec_hpp
#include <cstdlib>
#include <stdio.h>
#include "IntVec.hpp"
class RealVec
{
private:
    int dim;
public:
    double *val;
    
    RealVec();
    RealVec(int n);
    void SetDim(int r);
    ~RealVec();
    int GetDim() const;

    double Mag();
    double MagSq();
    double Dot(RealVec &v);
    double Dot(IntVec &v);
    void SetVal(double r);
    void SetVal(int r);
    void Zero();
    void Normalize();
        
    void Copy(RealVec &v);
    void Add(RealVec &v);
    void Sub(RealVec &v);
    void MulComps(RealVec &v);
    void DivComps(RealVec &v);

    void Copy(IntVec &v);
    void Add(IntVec &v);
    void Sub(IntVec &v);
    void MulComps(IntVec &v);
    void DivComps(IntVec &v);

    void Add(double r);
    void Sub(double r);
    void Mul(double r);
    void Div(double r);

    void Add(int r);
    void Sub(int r);
    void Mul(int r);
    void Div(int r);
    IntVec Mul(RealVec &v);
};

#endif /* RealVec_hpp */
