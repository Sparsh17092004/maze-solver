#include "DFSolver.h"
#include "Maze.h"
#include <stack>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void DFSolver::solve(const Maze &maze) {
    pair<int,int> start = maze.getStart();
    pair<int,int> end = maze.getEnd();


    vector<vector<int>> dist(maze.getRows(), vector<int>(maze.getCols(), -1));
    map<pair<int,int>, pair<int,int>> parent;
    

    stack<pair<int,int>> st;
    st.push(start);
    dist[start.first][start.second] = 0;
    parent[start] = start;

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while(!st.empty()) {
        pair<int,int> top = st.top();
        st.pop();
        int x = top.first, y = top.second;

        // Show current position being explored
        cout << "Exploring: (" << x << "," << y << ")\n";
        maze.printMaze(top);

        if (top == end) {
            cout << "Found the end!\n";
            break;
        }

        for (int k = 3; k >= 0; k--) {
            int nx = x + dx[k], ny = y + dy[k];
            pair<int,int> next = {nx, ny};
            if (maze.isValid(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                parent[next] = top;
                st.push(next);
            }
        }
    }

    // Reconstruct path
    if (parent.find(end) == parent.end()) {
        cout << "No path found with DFS!\n";
        return;
    }

    vector<pair<int,int>> path;
    for (pair<int,int> cur = end; cur != start; cur = parent[cur]) {
        path.push_back(cur);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    // Show final path
    cout << "\nFinal path:\n";
    maze.printMaze(end, path);
    cout << "\nDFS found a path of length " << path.size()-1 << ".\n";
}