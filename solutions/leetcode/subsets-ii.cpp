// https://leetcode.com/problems/subsets-ii/
// Week 3 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> Result;
    void Recur(vector<int>& nums, vector<int>& Case, int Start, int Count){
        if (Count == 0) {
            //
            for (const auto& Element : Result){
                if (Case.size() == Element.size()){
                    if(std::equal(Case.begin(), Case.end(), Element.begin(), Element.end())) return;
                }
            }
            
            Result.emplace_back(Case);
            return;
        }

        for (int i = Start; i < nums.size(); ++i) {
            Case.push_back(nums[i]);
            Recur(nums, Case, i + 1, Count - 1);
            Case.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i <= nums.size(); ++i){
            vector<int> Case;
            Recur(nums, Case, 0, i);
        }

        return Result;
    }
};