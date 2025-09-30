#pragma once
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <stdexcept>

class Maze {
private:
    std::vector<std::vector<char>> grid;
    int rows, cols;
    std::pair<int,int> start, end;
    
    void loadFromFile(const std::string& filename);
    
public:
    Maze(const std::string &filename);
    Maze(const std::string &filename, int startX, int startY, int endX, int endY);
    
    void printMaze(std::pair<int,int> current, const std::vector<std::pair<int,int>> &path = {}) const;
    bool isValid(int x, int y) const;

    std::pair<int,int> getStart() const { return start; }
    std::pair<int,int> getEnd() const { return end; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};