// https://leetcode.com/problems/koko-eating-bananas/
// Week 5 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int minEatingSpeed(vector<int>& piles, int h) {
    int Size = static_cast<int>(piles.size());
    int Front = 1;
    int End = *std::max_element(piles.begin(), piles.end());
    if (Size == h) return End;

    int Result = 0;

    while (Front <= End) {
        int Middle = (Front + End) / 2;
        int Hour = 0;
        for (const auto& Element : piles) {
            Hour += (Element + Middle - 1) / Middle;
            if (Hour > h) break;
        }

        if (Hour <= h) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
        
    return Result;
}