// https://leetcode.com/problems/binary-search/
// Week 5 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int>& nums, int target) {
    int Size = static_cast<int>(nums.size());
    if (Size == 1) return nums[0] == target ? 0 : -1;

    int Front = 0, End = Size - 1;
    while (Front <= End) { 
        int Middle = (Front + End) / 2;
        if (nums[Middle] == target) return Middle; 

        if (nums[Middle] > target) {
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    return -1;
}