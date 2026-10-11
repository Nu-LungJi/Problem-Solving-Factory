// https://leetcode.com/problems/contiguous-array/
// Week 4 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int Size = static_cast<int>(nums.size());
        if (Size == 1) return 0;
        unordered_map<int, int> SumMap;
        SumMap[0] = -1;

        int CurSum = 0;
        int Result = 0;

        for (int i = 0; i < Size; ++i) {
            CurSum += (nums[i] == 1 ? 1 : -1);

            if (SumMap.find(CurSum) != SumMap.end()) {
                int Length = i - SumMap[CurSum];
                Result = std::max(Result, Length);
            } else {
                SumMap[CurSum] = i;
            }
        }

        return Result;
    }
};