#include "LeapfrogIntegrator.hpp"

void LeapfrogIntegrator::Step(int part, Simulator& nmD1) {
    int n;
    if (part == 1) {
        for (int i = 0; i < nmD1.nAtom; i++) {
            for (int dId = 0; dId < nmD1.dim; dId++) {
                nmD1.v[3 * i + dId] += nmD1.a[3 * i + dId] * nmD1.delta_t;
                nmD1.x[3 * i + dId] += nmD1.v[3 * i + dId] * nmD1.delta_t;
            }
        }
    } else {
        for (int i = 0; i < nmD1.nAtom; i++) {
            for (int dId = 0; dId < nmD1.dim; dId++) {
                nmD1.v[3 * i + dId] += nmD1.a[3 * i + dId] * nmD1.delta_t;
            }
        }
    }
}
