#pragma once
#include "Solver.h"

class DFSolver : public Solver {
public:
    void solve(const Maze &maze) override;
};
