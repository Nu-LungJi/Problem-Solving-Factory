// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// Week 5 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> Result = {-1, -1};
    int Size = static_cast<int>(nums.size());
    if (Size == 0 || (Size == 1 && nums[0] != target)) return Result;

    auto EndIter = std::upper_bound(nums.begin(), nums.end(), target);
    auto StartIter = std::lower_bound(nums.begin(), nums.end(), target);

    Result[0] = StartIter - nums.begin();
    Result[1] = EndIter - nums.begin() - 1;
    if (Result[0] > Result[1]) return {-1, -1};
        
    return Result;
}

int main() {
    std::vector<int> Input = { 5,7,7,8,8,10 };
    auto Result = searchRange(Input, 8);
    
    for (const auto& Element : Result) std::cout << Element << " ";
    return 0;
}