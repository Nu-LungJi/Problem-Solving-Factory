// https://leetcode.com/problems/find-pivot-index/
// Week 4 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int Size = static_cast<int>(nums.size());
        vector<int> PrefixFront, PrefixBack;
        PrefixFront.emplace_back(0);
        PrefixBack.emplace_back(0);

        for (int i = 0; i < Size; ++i){
            PrefixBack.emplace_back(nums[Size - i - 1] + PrefixBack[i]);
        }

        for (int i = 0; i < Size; ++i){
            if (PrefixFront[i] == PrefixBack[Size - i - 1]) return i;
            PrefixFront.emplace_back(nums[i] + PrefixFront[i]);
        }

        return -1;
    }
};