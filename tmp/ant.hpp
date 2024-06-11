#pragma once

#include "organism.hpp"

class Ant : public Organism {
public:
    Ant(int r, int c);
    void move(Simulation* sim) override;
    void breed(Simulation* sim) override;
    void starve(Simulation* sim) override;
    OrganismType getType() const override { return ANT; }
    char getSymbol() const override { return 'a'; }
};

