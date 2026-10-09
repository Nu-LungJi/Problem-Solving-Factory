// https://leetcode.com/problems/maximum-average-subarray-i/
// Week 4 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double MaxAvg = -10000;
        int Size = static_cast<int>(nums.size());

        int Sum = 0, CurIdx = 0;
        for (int i = 0; i < k; ++i) Sum += nums[i];

        while (CurIdx + k <= Size) {
            MaxAvg = std::max(MaxAvg, static_cast<double>(Sum) / static_cast<double>(k));
            Sum -= nums[CurIdx++];
            if (CurIdx + k - 1 < Size) Sum += nums[CurIdx + k - 1];
        }

        return MaxAvg;
    }
};