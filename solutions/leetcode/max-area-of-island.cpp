// https://leetcode.com/problems/max-area-of-island/
// Week 6 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int Height, Width;
void DFS(vector<vector<int>>& grid, int i, int j, int& Max) {
    grid[i][j] = 0;
    Max++;
    if (i - 1 >= 0 && grid[i - 1][j] == 1) DFS(grid, i - 1, j, Max);
    if (i + 1 < Height && grid[i + 1][j] == 1) DFS(grid, i + 1, j, Max);
    if (j - 1 >= 0 && grid[i][j - 1] == 1) DFS(grid, i, j - 1, Max);
    if (j + 1 < Width && grid[i][j + 1] == 1) DFS(grid, i, j + 1, Max);
}
int maxAreaOfIsland(vector<vector<int>>& grid) {
    Height = static_cast<int>(grid.size());
    Width = static_cast<int>(grid[0].size());

    int Largest = 0;
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (grid[i][j] == 1){
                int Max = 0;
                DFS(grid, i, j, Max);
                Largest = std::max(Max, Largest);
            }
        }
    }
    return Largest;
}