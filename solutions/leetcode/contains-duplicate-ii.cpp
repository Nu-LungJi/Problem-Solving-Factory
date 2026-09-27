// https://leetcode.com/problems/contains-duplicate-ii/
// Week 2 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> IndexList;
    int Size = static_cast<int>(nums.size());
    for (int i = 0; i < Size; ++i){
        if (IndexList.count(nums[i]) > 0){
            if (std::abs(IndexList.find(nums[i])->second - i) <= k)
                return true;
        }
        IndexList[nums[i]] = i;
    }
    return false;
}

int main()
{
    vector<int> Input = {1,2,3,1,2,3};
    std::cout << boolalpha;
    std::cout << containsNearbyDuplicate(Input, 2);
    
    return 0;
}
