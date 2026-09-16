// https://leetcode.com/problems/running-sum-of-1d-array/
// Week 1 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> SumList;
        int PreviousSum = nums[0];
        SumList.emplace_back(PreviousSum);
        for (uint32_t i = 1; i < nums.size(); ++i){
            PreviousSum += nums[i];
            SumList.emplace_back(PreviousSum);
        }

        return SumList;
    }
};

int main()
{
    Solution S;
    vector<int> nums = { 1, 2, 3, 4 };
    
    const auto& SumList = S.runningSum(nums);
    for (const auto& Element : SumList)
    {
        std::cout << Element << " ";
    }
    return 0;
}