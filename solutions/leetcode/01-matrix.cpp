// https://leetcode.com/problems/01-matrix/
// Week 6 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

pair<int, int> ds[] = {{-1, 0},{1, 0}, {0, -1}, {0, 1}};

int Height, Width;
void BFS(vector<vector<int>>& mat) {
    queue<pair<int, int>> Queue;
        
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (mat[i][j] == 0) Queue.push({i, j});
            else mat[i][j] = -1;
        }
    }

    while (!Queue.empty()) {
        auto [x, y] = Queue.front();
        Queue.pop();

        for (int i = 0; i < 4; ++i) {
            int X = x + ds[i].first;
            int Y = y + ds[i].second;

            if (X >= 0 && X < Height && Y >= 0 && Y < Width && mat[X][Y] == -1) {
                mat[X][Y] = mat[x][y] + 1;
                Queue.push({X, Y});
            }
        }
    }
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    Height = static_cast<int>(mat.size());
    Width = static_cast<int>(mat[0].size());
    if ((Width == 1 && Height == 1) || (Width == 1 && Height == 2) || 
    (Width == 2 && Height == 1)) return mat;

    BFS(mat);
    return mat;
}