// https://leetcode.com/problems/range-sum-query-2d-immutable/
// Week 4 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& _matrix) {
        int OutGridSize = static_cast<int>(_matrix.size());
        for (int i = 0; i < OutGridSize; ++i) {
            int InGridSize = static_cast<int>(_matrix[i].size());
            for (int j = 1; j < InGridSize; ++j) {
                _matrix[i][j] += _matrix[i][j - 1]; // 가로
            }
        }
        for (int i = 1; i < OutGridSize; ++i) {
            int InGridSize = static_cast<int>(_matrix[i].size());
            for (int j = 0; j < InGridSize; ++j) {
                _matrix[i][j] += _matrix[i - 1][j];
            }
        }

        matrix = _matrix;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if (row1 == 0 && col1 == 0) {
            return matrix[row2][col2];
        } 
        else if (row1 == 0) {
            return matrix[row2][col2] - matrix[row2][col1 - 1];
        }
        else if (col1 == 0) {
            return matrix[row2][col2] - matrix[row1 - 1][col2];
        }
        else {
            return matrix[row2][col2] - matrix[row1 - 1][col2] 
            - matrix[row2][col1 - 1] + matrix[row1 - 1][col1 - 1];
        }

        return 0;
    }

private:
    vector<vector<int>> matrix;
};
// matrix[0] = { 3, 0, 1, 4, 2 }