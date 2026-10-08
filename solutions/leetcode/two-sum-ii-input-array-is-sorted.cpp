// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
// Week 4 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
    int FrontPTR = 0, BackPTR = static_cast<int>(numbers.size()) - 1;
    while (FrontPTR < BackPTR){
        int EvalValue = numbers[FrontPTR] + numbers[BackPTR];
        if      (EvalValue == target) break;
        EvalValue > target ? BackPTR-- : FrontPTR++;
    }
    return { FrontPTR + 1, BackPTR + 1 };
}