// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/
// Week 1 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        std::vector<bool> AbleToMaxCandyOwner;
        int MaxCandy = 0;
        for (auto& Element : candies){
            MaxCandy = std::max(MaxCandy, Element);
        }

        for (auto& Element : candies){
            AbleToMaxCandyOwner.emplace_back(MaxCandy <= Element + extraCandies);
        }

        return AbleToMaxCandyOwner;
    }
};

int main()
{
    cout << boolalpha;
    Solution S;
    vector<int> candies = { 4, 2, 1, 1, 2 };
    int extraCandies = 1;
    auto Result = S.kidsWithCandies(candies, extraCandies);
    
    for (bool R : Result)
    {
        std::cout << R << " ";
    }
    
    return 0;
}