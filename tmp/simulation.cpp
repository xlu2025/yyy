#include "simulation.hpp"
#include "ant.hpp"
#include "queen_ant.hpp"
#include "doodlebug.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Simulation::Simulation(int r, int c, int steps) : rows(r), cols(c), time_steps(steps) {
    grid.resize(rows, vector<Organism*>(cols, nullptr));
}

Simulation::~Simulation() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
    }
}

void Simulation::initialize() {
    srand(time(0));
    // Initialize grid with ants and doodlebugs at random positions
    // For example, using default values
    int numDoodlebugs = 15;
    int numAnts = 50;
    int numQueens = 2;

    // Add doodlebugs
    for (int i = 0; i < numDoodlebugs; ++i) {
        int r = rand() % rows;
        int c = rand() % cols;
        while (grid[r][c] != nullptr) {
            r = rand() % rows;
            c = rand() % cols;
        }
        grid[r][c] = new DoodleBug(r, c);
    }

    // Add queen ants
    for (int i = 0; i < numQueens; ++i) {
        int r = rand() % rows;
        int c = rand() % cols;
        while (grid[r][c] != nullptr) {
            r = rand() % rows;
            c = rand() % cols;
        }
        grid[r][c] = new QueenAnt(r, c);
    }

    // Add worker ants
    for (int i = 0; i < numAnts; ++i) {
        int r = rand() % rows;
        int c = rand() % cols;
        while (grid[r][c] != nullptr) {
            r = rand() % rows;
            c = rand() % cols;
        }
        grid[r][c] = new Ant(r, c);
    }
}

void Simulation::simulate() {
    for (int t = 0; t < time_steps; ++t) {
        // Move all doodlebugs first
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr && grid[i][j]->getType() == DOODLEBUG) {
                    grid[i][j]->move(this);
                }
            }
        }

        // Move all ants
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr && grid[i][j]->getType() == ANT) {
                    grid[i][j]->move(this);
                }
            }
        }

        // Handle breeding and starvation for all organisms
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr) {
                    grid[i][j]->breed(this);
                    grid[i][j]->starve(this);
                }
            }
        }

        // Print the grid
        printGrid();
    }
}

void Simulation::printGrid() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == nullptr) {
                cout << ".";
            }
            else {
                cout << grid[i][j]->getSymbol();
            }
        }
        cout << endl;
    }
    cout << "\n\n\n\n\n\n";
}

bool Simulation::isInBounds(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

bool Simulation::isCellEmpty(int r, int c) const {
    return grid[r][c] == nullptr;
}

bool Simulation::isAnt(int r, int c) const {
    return grid[r][c] != nullptr && grid[r][c]->getType() == ANT;
}

void Simulation::moveOrganism(int oldRow, int oldCol, int newRow, int newCol) {
    grid[newRow][newCol] = grid[oldRow][oldCol];
    grid[oldRow][oldCol] = nullptr;
}

void Simulation::addOrganism(Organism* org) {
    grid[org->getRow()][org->getCol()] = org;
}

void Simulation::removeOrganism(int r, int c) {
    delete grid[r][c];
    grid[r][c] = nullptr;
}
