// https://leetcode.com/problems/plus-one/
// Week 1 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        unsigned int VectorSize = digits.size();

        auto Result = RecursiveCheck(digits, VectorSize - 1);
        if (Result.empty()) {
            Result.emplace_back(1);
            for (int i = 0; i < VectorSize; ++i){
                Result.emplace_back(0);
            }
        }
        return Result;
    }
    vector<int> RecursiveCheck(vector<int>& digits, int CurrentIDX) {
        int Value = digits[CurrentIDX] + 1;
        if (Value < 10){
            digits[CurrentIDX] = Value;
            return digits;
        }
        else {
            digits[CurrentIDX] = 0;
            if (CurrentIDX - 1 >= 0){
                return RecursiveCheck(digits, CurrentIDX - 1);
            }
            else {
                digits.clear();
                return digits;
            }
        }
    }
};

int main()
{
    Solution S;
    std::array<int, 3> A{1, 2, 3};
    vector<int> Input = {9,8,7,6,5,4,3,2,1,0};
    const auto& Result = S.plusOne(Input);
    
    for (const auto& Element : Result)
    {
        std::cout << Element << " ";
    }
    
    return 0;
}