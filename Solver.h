#pragma once
#include "Maze.h"

class Solver {
public:
    virtual void solve(const Maze &maze) = 0; // pure virtual
    virtual ~Solver() {}
};
