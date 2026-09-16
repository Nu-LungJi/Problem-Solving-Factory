// https://leetcode.com/problems/richest-customer-wealth/
// Week 1 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int MaxAsset = 0;
        for (std::vector<int>& Array : accounts){
            MaxAsset = std::max(MaxAsset, accumulate(Array.begin(), Array.end(), 0));
        }
        return MaxAsset;
    }
};