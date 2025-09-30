#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

Maze::Maze(const string &filename) {
    loadFromFile(filename);
}

Maze::Maze(const string &filename, int startX, int startY, int endX, int endY) {
    loadFromFile(filename);
    start = {startX, startY};
    end = {endX, endY};
    
    if (!isValid(start.first, start.second) || !isValid(end.first, end.second)) {
        throw runtime_error("Invalid start or end position");
    }
}

void Maze::loadFromFile(const string &filename) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Cannot open file: " + filename);
    }

    in >> rows >> cols;
    grid.resize(rows, vector<char>(cols));
    
    string line;
    getline(in, line); // Consume the newline after rows/cols
    
    for(int i = 0; i < rows; i++) {
        getline(in, line);
        for(int j = 0; j < cols && j < line.length(); j++) {
            grid[i][j] = line[j];
        }
    }
    
    // These will be overridden if using custom positions
    in >> start.first >> start.second;
    in >> end.first >> end.second;
}

void Maze::printMaze(pair<int,int> current, const vector<pair<int,int>> &path) const {
    // Print the legend
    cout << "\n=== Maze Legend ===\n";
    cout << "S - Start Position\n";
    cout << "E - End/Goal Position\n";
    cout << "* - Current Position\n";
    cout << "o - Path Taken\n";
    cout << "# - Wall/Obstacle\n";
    cout << ". - Empty/Open Space\n";
    cout << "==================\n\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            pair<int,int> cell = {i,j};
            
            if (cell == current) 
                cout << "* ";
            else if (cell == start) 
                cout << "S ";
            else if (cell == end) 
                cout << "E ";
            else if (find(path.begin(), path.end(), cell) != path.end()) 
                cout << "o ";
            else if (grid[i][j] == '#') 
                cout << "# ";
            else 
                cout << ". ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    #ifdef _WIN32
    Sleep(200);
    #else
    this_thread::sleep_for(chrono::milliseconds(200));
    #endif
}

bool Maze::isValid(int x, int y) const {
    return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] != '#';
}