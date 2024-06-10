#include "SimulationManager.hpp"

int main(int argc, const char * argv[]) {
    const char* inpName = "/Users/hyuqing/Downloads/research/MD3/MD3/Values_Input.txt";
    SimulationManager simManager(inpName);
    simManager.Run();
    std::cout << "Completed" << std::endl;
    return 0;
}
