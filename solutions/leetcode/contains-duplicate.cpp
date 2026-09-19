// https://leetcode.com/problems/contains-duplicate/
// Week 1 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        auto unique_iter = std::unique(nums.begin(), nums.end());

        if (unique_iter == nums.end()) return false;

        return true;
    }
};

int main() {
    Solution S;
    
    std::cout << boolalpha;
    
    vector<int> NumbersA = {1, 2, 3, 1};
    std::cout << S.containsDuplicate(NumbersA) << "\n";
    
    vector<int> NumbersB = {1, 2, 3, 4};
    std::cout << S.containsDuplicate(NumbersB) << "\n";
    return 0;
}