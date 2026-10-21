// https://leetcode.com/problems/flood-fill/
// Week 6 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    int originalColor = image[sr][sc];
    if (originalColor == color) return image;
    int n = static_cast<int>(image.size());
    int m = static_cast<int>(image[0].size());

    stack<pair<int, int>> Stack; 
    Stack.push({sr, sc});

    while (!Stack.empty()) {
        pair<int, int> Top = Stack.top();
        Stack.pop();

        image[Top.first][Top.second] = color;

        if (Top.first - 1 >= 0 && originalColor == image[Top.first - 1][Top.second]) Stack.push({Top.first - 1, Top.second});
        if (Top.first + 1 < n && originalColor == image[Top.first + 1][Top.second])  Stack.push({Top.first + 1, Top.second});
        if (Top.second - 1 >= 0 && originalColor == image[Top.first][Top.second - 1]) Stack.push({Top.first, Top.second - 1});
        if (Top.second + 1 < m && originalColor == image[Top.first][Top.second + 1])  Stack.push({Top.first, Top.second + 1});
    }
    return image;
}