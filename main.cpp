#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Maze.h"
#include "BFSolver.h"
#include "DFSolver.h"

using namespace std;

vector<string> readMazeFromConsole() {
    vector<string> maze;
    string line;
    int rows, cols;
    
    cout << "Enter number of rows and columns (e.g., 5 5): ";
    cin >> rows >> cols;
    cin.ignore(1000, '\n');
    
    cout << "Enter the maze row by row (use . for path, # for wall):\n";
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i+1 << ": ";
        getline(cin, line);
        if (line.length() != cols) {
            cout << "Invalid length! Please enter exactly " << cols << " characters.\n";
            i--; // Retry this row
            continue;
        }
        maze.push_back(line);
    }
    return maze;
}

void saveMazeToFile(const vector<string>& maze, const string& filename) {
    ofstream out(filename);
    out << maze.size() << " " << (maze.empty() ? 0 : maze[0].length()) << "\n";
    for (const auto& row : maze) {
        out << row << "\n";
    }
    out.close();
}

void solveMaze(Maze& maze) {
    while (true) {
        cout << "\n1. Solve with DFS\n";
        cout << "2. Solve with BFS\n";
        cout << "3. Back to main menu\n";
        cout << "Enter choice (1-3): ";
        
        int choice;
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) {
            DFSolver dfs;
            dfs.solve(maze);
        }
        else if (choice == 2) {
            BFSolver bfs;
            bfs.solve(maze);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    string filename = "maze.txt";
    int choice;

    while (true) {
        cout << "\n=== Maze Solver ===\n";
        cout << "1. Use default maze\n";
        cout << "2. Enter custom maze\n";
        cout << "3. Exit\n";
        cout << "Enter choice (1-3): ";
        
        cin >> choice;
        cin.ignore(1000, '\n');

        try {
            if (choice == 1) {
                Maze maze(filename);
                solveMaze(maze);
            }
            else if (choice == 2) {
                auto customMaze = readMazeFromConsole();
                
                int startX, startY, endX, endY;
                cout << "Enter start position (row col, 0-based): ";
                cin >> startX >> startY;
                cout << "Enter end position (row col, 0-based): ";
                cin >> endX >> endY;
                cin.ignore(1000, '\n');

                saveMazeToFile(customMaze, "temp_maze.txt");
                Maze maze("temp_maze.txt", startX, startY, endX, endY);
                solveMaze(maze);
            }
            else if (choice == 3) {
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
            cin.ignore(1000, '\n');
        }
    }

    return 0;
}