// https://leetcode.com/problems/search-insert-position/
// Week 5 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int searchInsert(vector<int>& nums, int target) {
    int Size = static_cast<int>(nums.size());
    int Front = 0, End = Size - 1;
    if (Size == 0) return 0;

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

    if      (nums.front() > target) return 0;
    else if (nums.back()  < target) return Size;

    for (int i = 1; i < Size; ++i) {
        if (nums[i] > target && nums[i - 1] < target) return i;
    }

    return End;
}