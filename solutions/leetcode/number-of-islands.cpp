// https://leetcode.com/problems/number-of-islands/
// Week 6 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int Height, Width;
void DFS(vector<vector<char>>& grid, int i, int j) {
    grid[i][j] = '0';
    if (i - 1 >= 0 && grid[i - 1][j] == '1') DFS(grid, i - 1, j);
    if (i + 1 < Height && grid[i + 1][j] == '1') DFS(grid, i + 1, j);
    if (j - 1 >= 0 && grid[i][j - 1] == '1') DFS(grid, i, j - 1);
    if (j + 1 < Width && grid[i][j + 1] == '1') DFS(grid, i, j + 1);
}
int numIslands(vector<vector<char>>& grid) {
    Height = static_cast<int>(grid.size());
    Width = static_cast<int>(grid[0].size());

    int IslandCount = 0;
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (grid[i][j] == '1') {
                DFS(grid, i, j);
                IslandCount++;
            }
        }
    }
    return IslandCount;
}