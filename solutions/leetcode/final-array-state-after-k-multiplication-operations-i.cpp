// https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/
// Week 2 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
    size_t Size = nums.size();
    while (k--){
        int Minimum = nums[0], MinIndex = 0;
        for (size_t i = 1 ; i < Size; ++i){
            if (Minimum > nums[i]){
                Minimum = nums[i];
                MinIndex = i;
            }
        }

        nums[MinIndex] *= multiplier;
    }
        
    return nums;
}

int main()
{
    auto Input = vector<int>{2,1,3,5,6};
    auto Output = getFinalState(Input, 5, 2);
    
    for (const auto& Element : Output)
    {
        std::cout << Element << " ";
    }
    
    return 0;
}