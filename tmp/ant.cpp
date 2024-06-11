#include "ant.hpp"
#include "simulation.hpp"
#include <cstdlib>
#include <ctime>

Ant::Ant(int r, int c) : Organism(r, c) {}

// Move method for Ant
void Ant::move(Simulation* sim) {
    static const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Up, Down, Left, Right
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // 4 corners
    };

    int dir = rand() % 8;
    int newRow = row + directions[dir][0];
    int newCol = col + directions[dir][1];

    if (sim->isInBounds(newRow, newCol) && sim->isCellEmpty(newRow, newCol)) {
        sim->moveOrganism(row, col, newRow, newCol);
        row = newRow;
        col = newCol;
    }
    moved = true;
    steps++;
}

// Breed method for Ant
void Ant::breed(Simulation* sim) {
    if (steps >= 3) {
        static const int directions[8][2] = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Up, Down, Left, Right
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // 4 corners
        };

        for (int i = 0; i < 8; ++i) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (sim->isInBounds(newRow, newCol) && sim->isCellEmpty(newRow, newCol)) {
                sim->addOrganism(new Ant(newRow, newCol));
                steps = 0;
                break;
            }
        }
    }
}

// Starve method for Ant
void Ant::starve(Simulation* sim) {
    if (steps >= 5) {
        sim->removeOrganism(row, col);
    }
}
