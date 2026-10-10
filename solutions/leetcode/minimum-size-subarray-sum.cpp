// https://leetcode.com/problems/minimum-size-subarray-sum/
// Week 4 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int Size = static_cast<int>(nums.size());

        int CurFront = 0, CurBack = 0, Sum = 0, Min = INT_MAX;
        
        while (CurFront <= CurBack && CurBack != Size) {
            Sum += nums[CurBack++];
            while (Sum >= target) {
                Min = std::min(Min, CurBack - CurFront);
                Sum -= nums[CurFront++];
            }
        }

        return Min == INT_MAX ? 0 : Min;
    }
};