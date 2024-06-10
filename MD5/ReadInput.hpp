

#ifndef ReadInput_hpp
#define ReadInput_hpp
#include <string>
#include <vector>
#include <fstream>
#include "ReadFile.hpp"
class ReadInput{
private:
    ReadFile rf;
    char inpFname[128];
public:
    ReadInput(const char Fname[]);
    int nAtomsSA, nTypesSA;
    int nAtoms, dim;
    int nEval, nLimit;
    double dtSA,*massSA, temp, density;
    void ReadParameterFile();
    void GetNextLine(int numArgs, std::string keyWord);
    void GetNextLine(int numArgs);
    void GetNextLine();
    void SetEvalParameters(int nEval, int nLimit);
    int GetNAtoms();
    int GetNAtomsSA();
    int GetNTypesSA();
    double GetMassSA(int id);
    int GetNEval();
    int GetNLimit();
    
    int GetDim();
    double GetdtSA();
    double Gettemp();
    double Getdensity();
};

#endif /* ReadInput_hpp */
