// https://leetcode.com/problems/subsets/
// Week 3 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool MakeCase(vector<vector<int>>& Result, vector<int>& nums, vector<int>& Case, int Start, int Count) {
    if (Count == 0) {
        Result.emplace_back(Case);
        return true;
    }
    if (nums.size() - Start < Count) return false;

    for (int i = Start; i < nums.size(); ++i){
        Case.emplace_back(nums[i]);
        MakeCase(Result, nums, Case, i + 1, Count - 1);
        Case.pop_back();
    }

    return true;
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> Result;
    for (int i = 0; i <= nums.size(); ++i){
        vector<int> Case;
        MakeCase(Result, nums, Case, 0, i);
    }

    return Result;
}