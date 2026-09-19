// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// Week 1 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return std::unique(nums.begin(), nums.end()) - nums.begin();
    }
};

int main()
{
    Solution S;
    vector<int> Numb = { 12, 34, 3, 25, 7, 9, 4 };
    cout << S.removeDuplicates(Numb) << "\n";
    
    return 0;
}