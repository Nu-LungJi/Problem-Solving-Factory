// https://leetcode.com/problems/squares-of-a-sorted-array/
// Week 4 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> sortedSquares(vector<int>& nums) {
    int Size = static_cast<int>(nums.size());
    int FrontPTR = 0, BackPTR = Size - 1;
        
    vector<int> Result(Size, 0); int Curr = BackPTR;

    while (Curr >= 0) {
        int Front = nums[FrontPTR] * nums[FrontPTR];
        int Back = nums[BackPTR] * nums[BackPTR];
        if (Front == Back && FrontPTR != BackPTR){
            FrontPTR++; BackPTR--;
            Result[Curr--] = Front;
            Result[Curr--] = Front;
        }
        else if (Front < Back) {
            BackPTR--;
            Result[Curr--] = Back;
        }
        else {
            FrontPTR++;
            Result[Curr--] = Front;
        }
    }
        
    return Result;
}