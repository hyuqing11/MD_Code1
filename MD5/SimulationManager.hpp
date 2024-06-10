#ifndef SimulationManager_hpp
#define SimulationManager_hpp

#include "ReadInput.hpp"
#include "Simulator.hpp"
#include "ComputerForce.hpp"
#include "LeapfrogIntegrator.hpp"

class SimulationManager {
public:
    SimulationManager(const char* inputFileName);
    void Run();

private:
    Simulator* nmD1;
    ComputerForce* computeForce;
    LeapfrogIntegrator integrator;
    ReadInput rIn;
};

#endif /* SimulationManager_hpp */
