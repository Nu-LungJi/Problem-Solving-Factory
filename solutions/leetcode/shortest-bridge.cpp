// https://leetcode.com/problems/shortest-bridge/
// Week 6 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

class Solution {
public:
    queue<pair<int, int>> Queue;
    void FindIslands(int i, int j, vector<vector<int>>& grid) {
        int Size = static_cast<int>(grid.size());
        if (i < 0 || i >= Size || j < 0 || j >= Size || grid[i][j] != 1) return;

        queue<pair<int, int>> iSland;

        grid[i][j] = 2;
        iSland.push({i, j});
        Queue.push({i, j});

        while (!iSland.empty()) {
    auto [x, y] = iSland.front();
    iSland.pop();

    for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx >= 0 && nx < Size && 
            ny >= 0 && ny < Size && 
            grid[nx][ny] == 1) {
            grid[nx][ny] = 2;
            iSland.push({nx, ny});
            Queue.push({nx, ny});
        }
    }
}
    }

    int BFS(vector<vector<int>>& grid) {
    int Size = static_cast<int>(grid.size());
    int Step = 0;

    while (!Queue.empty()) {
        int Count = Queue.size();

        for (int i = 0; i < Count; ++i) {
            auto [x, y] = Queue.front();
            Queue.pop();

            for (int j = 0; j < 4; ++j) {
                int X = x + dx[j];
                int Y = y + dy[j];

                if (X >= 0 && X < Size && Y >= 0 && Y < Size) {
                    if (grid[X][Y] == 1)
                        return Step;

                    if (grid[X][Y] == 0) {
                        grid[X][Y] = 2;
                        Queue.push({X, Y});
                    }
                }
            }
        }

        Step++;
    }

    return -1;
}
    int shortestBridge(vector<vector<int>>& grid) {
        int Size = static_cast<int>(grid.size());
        Queue = queue<pair<int, int>>();
        bool Found = false;
        for (int i = 0; i < Size; ++i) {
            for (int j = 0; j < Size; ++j) {
                if (!Found && grid[i][j] == 1) {
                    Found = true;
                    FindIslands(i, j, grid);
                    break;
                }
            }
            if (Found) break;
        }

        return BFS(grid);
    }
};