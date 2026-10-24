// https://leetcode.com/problems/map-of-highest-peak/
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
    int Height, Width;
    void BFS(vector<vector<int>>& isWater) {
        queue<pair<int, int>> Queue;
        for (int i = 0; i < Height; ++i) {
            for (int j = 0; j < Width; ++j) {
                if (isWater[i][j] == 1) {
                    Queue.push({i, j});
                    isWater[i][j] = 0;
                }
                else {
                    isWater[i][j] = -1;
                }
            }
        }

        while (!Queue.empty()) {
            auto [x, y] = Queue.front();
            Queue.pop();

            for (int i = 0; i < 4; ++i) {
                int X = x + ds[i].first;
                int Y = y + ds[i].second;

                if (X >= 0 && X < Height && Y >= 0 && Y < Width && isWater[X][Y] == -1) {
                    isWater[X][Y] = isWater[x][y] + 1;
                    Queue.push({X, Y});
                }
            }
        }
    }
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        Height = static_cast<int>(isWater.size());
        Width = static_cast<int>(isWater[0].size());

        BFS(isWater);
        return isWater;
    }
};