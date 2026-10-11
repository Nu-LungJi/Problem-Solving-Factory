// https://leetcode.com/problems/maximum-subarray/
// Week 4 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int Size = static_cast<int>(nums.size());
    if (Size == 1) return nums[0];
    int Result = nums[0];
        
    int MinPrefix = 0, CurSum = 0;
    for (int i = 0; i < Size; ++i) {
        CurSum += nums[i];
        Result = std::max(Result, CurSum - MinPrefix);
        MinPrefix = std::min(MinPrefix, CurSum);
    }

    return Result;
}