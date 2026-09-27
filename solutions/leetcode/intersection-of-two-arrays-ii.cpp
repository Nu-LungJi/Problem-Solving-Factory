// https://leetcode.com/problems/intersection-of-two-arrays-ii/
// Week 2 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> Result;
    multiset<int> MS1(nums1.begin(), nums1.end());
    multiset<int> MS2(nums2.begin(), nums2.end());

    for (auto iter = MS1.begin(); iter != MS1.end();){
        auto Value = *iter;
        auto MS1Count = MS1.count(Value);
        auto MS2Count = MS2.count(Value);
        int Minimum = std::min(MS1Count, MS2Count);

        if (Minimum == 0) {
            iter++;
            continue;
        }

        while (Minimum--) Result.emplace_back(Value);
        while (MS1Count--) iter++;
    }

    return Result;
}

int main()
{
    vector<int> InputA = {4,9,5};
    vector<int> InputB = {9,4,9,8,4};
    
    auto Result = intersect(InputA, InputB);
    
    for (const auto& Element : Result)
    {
        std::cout << Element << " ";
    }
    
    return 0;
}