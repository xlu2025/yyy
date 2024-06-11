#include "simulation.hpp"
#include <iostream>

int main() {
    int rows = 100;
    int cols = 100;
    int time_steps =20; // Or any number of steps you want to simulate

    Simulation sim(rows, cols, time_steps);
    sim.initialize();
    sim.simulate();

    return 0;
}
