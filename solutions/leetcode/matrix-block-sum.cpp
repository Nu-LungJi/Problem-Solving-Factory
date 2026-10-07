// https://leetcode.com/problems/matrix-block-sum/
// Week 4 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int GridColSize = static_cast<int>(mat.size());
        int GridRowSize = static_cast<int>(mat[0].size());

        for (int i = 0; i < GridColSize; ++i) {
            for (int j = 1; j < GridRowSize; ++j) {
                mat[i][j] = mat[i][j] + mat[i][j - 1];
            }
        }
        
        for (int i = 1; i < GridColSize; ++i){
            for (int j = 0; j < GridRowSize; ++j) {
                mat[i][j] += mat[i - 1][j];
            }
        }

        vector<vector<int>> GridAnswer(GridColSize, vector<int>(GridRowSize, 0));

        for (int i = 0; i < GridColSize; ++i) {
            for (int j = 0; j < GridRowSize; ++j) {
                int r1 = max(0, i - k);
                int c1 = max(0, j - k);
                int r2 = min(GridColSize - 1, i + k);
                int c2 = min(GridRowSize - 1, j + k);

                int totalSum = mat[r2][c2];
                if (r1 > 0) {
                    totalSum -= mat[r1 - 1][c2];
                }
                if (c1 > 0) {
                    totalSum -= mat[r2][c1 - 1];
                }
                if (r1 > 0 && c1 > 0) {
                    totalSum += mat[r1 - 1][c1 - 1];
                }

                GridAnswer[i][j] = totalSum;
            }
        }

        return GridAnswer;
    }
};