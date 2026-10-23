// https://leetcode.com/problems/shortest-path-in-binary-matrix/
// Week 6 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int BFS(vector<vector<int>>& grid) {
    int Size = static_cast<int>(grid.size());
    queue<pair<int, int>> Queue;
    Queue.push({0, 0});

    grid[0][0] = 1;

    int Step = 1;

    while (!Queue.empty()) {
        int Count = static_cast<int>(Queue.size());
        for (int i = 0; i < Count; ++i) {
            pair<int, int> Top = Queue.front();
            Queue.pop();

            if (Top.first == Size - 1 && Top.second == Size - 1) return Step;

            for (int i = 0; i < 8; ++i) {
                int X = Top.first + dx[i];
                int Y = Top.second + dy[i];
                if (X >= 0 && X < Size && 
                    Y >= 0 && Y < Size) {
                    if (grid[X][Y] == 0){
                        grid[X][Y] = 1;
                        Queue.push({X, Y});
                    }
                    }
            }
        }
        Step++;
    }

    return -1;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int Size = static_cast<int>(grid.size());
    if (grid[0][0] == 1 || grid[Size - 1][Size - 1]) return -1;

    return BFS(grid);
}