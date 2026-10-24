// https://leetcode.com/problems/as-far-from-land-as-possible/
// Week 6 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

pair<int, int> ds[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
    int Size;
    int BFS(vector<vector<int>>& grid) {
        int MaxDistance = -1;
        bool ExistLand = false, ExistWater = false;
        queue<pair<int, int>> Queue;
        for (int i = 0; i < Size; ++i) {
            for (int j = 0; j < Size; ++j) {
                if (grid[i][j] == 1) {
                    Queue.push({i, j});
                    grid[i][j] = 0;
                    ExistLand = true;
                }
                else {
                    grid[i][j] = -1;
                    ExistWater = true;
                }
            }
        }

        if (!ExistLand || !ExistWater) return -1;

        while (!Queue.empty()) {
            auto [x, y] = Queue.front();
            Queue.pop();

            for (int i = 0; i < 4; ++i) {
                int X = x + ds[i].first;
                int Y = y + ds[i].second;

                if (X >= 0 && X < Size && Y >= 0 && Y < Size && grid[X][Y] == -1) {
                    grid[X][Y] = grid[x][y] + 1;
                    Queue.push({X, Y});
                }
            }
        }

        for (int i = 0; i < Size; ++i) {
            for (int j = 0; j < Size; ++j) {
                MaxDistance = std::max(MaxDistance, grid[i][j]);
            }
        }

        return MaxDistance;
    }
    int maxDistance(vector<vector<int>>& grid) {
        Size = static_cast<int>(grid.size());
        if (Size == 1) return 0;

        return BFS(grid);
    }
};