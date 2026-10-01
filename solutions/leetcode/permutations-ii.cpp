// https://leetcode.com/problems/permutations-ii/
// Week 3 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> Result;
    std::sort(nums.begin(), nums.end());
    do{
        Result.emplace_back(vector<int>{nums});
    }while (std::next_permutation(nums.begin(), nums.end()));
    return Result;
}

