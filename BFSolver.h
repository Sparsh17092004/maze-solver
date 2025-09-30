#pragma once
#include "Solver.h"
#include <queue>
#include <map>
#include <vector>

class BFSolver : public Solver {
public:
    void solve(const Maze &maze) override;
};
