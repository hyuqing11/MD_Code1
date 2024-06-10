#include "SimulationManager.hpp"
#include <iostream>

SimulationManager::SimulationManager(const char* inputFileName) : rIn(inputFileName) {
    rIn.ReadParameterFile();
    nmD1 = new Simulator(rIn);
    nmD1->Initialization();
    computeForce = new ComputerForce(*nmD1);
}

void SimulationManager::Run() {
    int nebrNow = 1, stepCount = 0;
    double dispHi;

    for (int stp = 0; stp < rIn.GetNLimit(); stp++) {
        std::cout << "step: " << stp << std::endl;
        ++stepCount;
        integrator.Step(1, *nmD1);
        
        if (nebrNow == 0) {
            nebrNow = 0;
            dispHi = 0;
            computeForce->BuildNebrList();
        }

        for (int i = 0; i < nmD1->nAtom; i++) {
            for (int dId = 0; dId < nmD1->dim; dId++) {
                computeForce->ApplyBoundaryCondition(nmD1->x[3 * i + dId], dId);
            }
        }
        
        computeForce->computer_force();
        integrator.Step(2, *nmD1);
    }
}

