#pragma once

#include "organism.hpp"
#include <vector>

class Simulation {
private:
    int rows;
    int cols;
    int time_steps;
    vector<vector<Organism*>> grid;

public:
    Simulation(int r, int c, int steps);
    ~Simulation();

    void initialize();
    void simulate();
    void printGrid() const;

    bool isInBounds(int r, int c) const;
    bool isCellEmpty(int r, int c) const;
    bool isAnt(int r, int c) const;

    void moveOrganism(int oldRow, int oldCol, int newRow, int newCol);
    void addOrganism(Organism* org);
    void removeOrganism(int r, int c);
};
