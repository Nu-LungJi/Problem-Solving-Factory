// https://leetcode.com/problems/binary-search/
// Week 5 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int>& nums, int target) {
    int Size = static_cast<int>(nums.size());
    if (Size == 0 || (Size == 1 && nums[0] != target)) return -1;

    int Front = 0, End = Size - 1;
    while (Front <= End) {
        int Middle = Front + (End - Front) / 2;
        if (nums[Middle] == target) return Middle;
        else if (nums[Middle] > target) {
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }

    return -1;
}