// https://leetcode.com/problems/permutations/
// Week 3 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> Result;
    do {
        vector<int> Array = nums;
        Result.emplace_back(Array);
    }while(std::next_permutation(nums.begin(), nums.end()));
    return Result;
}

vector<vector<int>> Result;
void BackTrack(int Count, vector<int>& nums){
    if (Count == nums.size()){
        Result.emplace_back(nums);
        return;
    }
        
    for (int i = Count; i < nums.size(); i++) {
        std::swap(nums[Count], nums[i]);
        BackTrack(Count + 1, nums);
        std::swap(nums[Count], nums[i]);
    }
}

vector<vector<int>> permute_Real(vector<int>& nums) {
    BackTrack(0, nums);
    return Result;
}