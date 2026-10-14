// https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
// Week 5 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int shipWithinDays(vector<int>& weights, int days) {
    int Size = static_cast<int>(weights.size());
    int Front = *std::max_element(weights.begin(), weights.end()), End = 0;

    for (const auto& Element : weights) End += Element;

    if (Size == 1) return End;

    int Result = 0;

    while (Front <= End) {
        int Middle = (Front + End) / 2;
        int Day = 1, Stack = 0;

        for (const auto& Element : weights) {
            if (Middle < Stack + Element) {
                Day++; Stack = 0;
            }
            Stack += Element;
            if (Day > days) break;
        }

        if (Day <= days) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }

    return Result;
}