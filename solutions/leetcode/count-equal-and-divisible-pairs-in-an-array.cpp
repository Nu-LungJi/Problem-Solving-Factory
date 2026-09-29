// https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/
// Week 3 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int countPairs(vector<int>& nums, int k) {
    int Count = 0;
    int Size = static_cast<int>(nums.size());
    for (int i = 0; i < Size - 1; ++i){
        for (int j = i + 1; j < Size; ++j){
            if (nums[i] == nums[j] && (i*j) % k == 0) Count++;
        }
    }
    return Count;
}

int main() {
    vector<int> Input = {3,1,2,2,2,1,3};
    std::cout << countPairs(Input, 2);
    return 0;
}