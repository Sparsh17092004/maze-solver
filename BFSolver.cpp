#include "BFSolver.h"
#include <iostream>
#include <algorithm>
using namespace std;

void BFSolver::solve(const Maze &maze) {
    pair<int,int> start = maze.getStart();
    pair<int,int> end = maze.getEnd();

    vector<vector<int>> dist(maze.getRows(), vector<int>(maze.getCols(), -1));
    map<pair<int,int>, pair<int,int>> parent;

    queue<pair<int,int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    parent[start] = start;

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while(!q.empty()) {
        pair<int,int> front = q.front(); q.pop();
        int x = front.first, y = front.second;

        maze.printMaze(front);

        if(front == end) break;

        for(int k = 0; k < 4; k++) {
             int nx = x + dx[k], ny = y + dy[k];
            pair<int,int> next = {nx, ny};
            if(maze.isValid(nx, ny) && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    parent[next] = front;
                    q.push(next);
                    }
            }
    }

    if(parent.find(end) == parent.end()) {
        cout << "No path found with BFS!\n";
        return;
    }

    vector<pair<int,int>> path;
    for(pair<int,int> cur = end; cur != start; cur = parent[cur])
        path.push_back(cur);
    path.push_back(start);
    reverse(path.begin(), path.end());

    maze.printMaze(end, path);
    cout << "\nBFS found path in " << dist[end.first][end.second] << " steps.\n";
}
