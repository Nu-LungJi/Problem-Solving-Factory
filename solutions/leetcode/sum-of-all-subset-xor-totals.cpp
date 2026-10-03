// https://leetcode.com/problems/sum-of-all-subset-xor-totals/
// Week 3 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int BitCal(vector<int>& Case){
        int Result = Case.front();
        for (int i = 1; i < Case.size(); ++i){
            Result = Result ^ Case[i];
        }
        return Result;
    }
    void Recur(int& Result, vector<int>& nums, vector<int>& Case, int Start, int Count){
        if (Count == 0) {
            Result += BitCal(Case);
            return;
        }

        for (int i = Start; i < nums.size(); ++i) {
            Case.push_back(nums[i]);
            Recur(Result, nums, Case, i + 1, Count - 1);
            Case.pop_back();
        }
    }

    int subsetXORSum(vector<int>& nums) {
        int Result = std::accumulate(nums.begin(), nums.end(), 0);
        for (int i = 2; i <= nums.size(); ++i){
            vector<int> Case;
            Recur(Result, nums, Case, 0, i);
        }

        return Result;
    }
};