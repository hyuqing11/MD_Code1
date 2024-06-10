#ifndef LeapfrogIntegrator_hpp
#define LeapfrogIntegrator_hpp

#include "Simulator.hpp"

class LeapfrogIntegrator {
public:
    void Step(int part, Simulator& nmD1);
};

#endif /* LeapfrogIntegrator_hpp */
