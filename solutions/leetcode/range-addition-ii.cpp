// https://leetcode.com/problems/range-addition-ii/
// Week 4 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        if (ops.empty()) return m * n;

        int MinOpsVertical = m,MinOpsHorizontal = n;

        for (const auto& operation : ops){
            MinOpsVertical = std::min(MinOpsVertical, operation[0]);
            MinOpsHorizontal = std::min(MinOpsHorizontal, operation[1]);
        }

        return MinOpsVertical * MinOpsHorizontal;
    }
};