// https://leetcode.com/problems/rotting-oranges/
// Week 6 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int Height, Width;
pair<int, int> ds[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int BFS(vector<vector<int>>& grid) {
    queue<std::pair<int, int>> Queue;
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (grid[i][j] == 2) {
                Queue.push({i, j});
                grid[i][j] = 0;
            }
            else if (grid[i][j] == 1) {
                grid[i][j] = -1;
            }
        }
    }
    int MaxDist = 0;
    while (!Queue.empty()) {
        auto [x, y] = Queue.front();
        Queue.pop();

        for (int i = 0; i < 4; ++i) {
            int X = x + ds[i].first;
            int Y = y + ds[i].second;
            
            if (X >= 0 && Y >= 0 && X < Height && Y < Width && grid[X][Y] == -1) {
                grid[X][Y] = grid[x][y] + 1;
                MaxDist = std::max(MaxDist, grid[X][Y]);
                Queue.push({X, Y});
            } 
        }
    }
    
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (grid[i][j] == -1) return -1;
        }
    }
    return MaxDist;
}

int orangesRotting(vector<vector<int>>& grid) {
    Height = static_cast<int>(grid.size());
    Width = static_cast<int>(grid[0].size());
    if (Height == 1 && Width == 1) return grid[0][0] == 0 ? 0 : grid[0][0] == 2 ? 0 : -1;
    
    return BFS(grid);
}