// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
// Week 5 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int smallestDivisor(vector<int>& nums, int threshold) {
    int Size = static_cast<int>(nums.size());

    int Front = 1, End = *std::max_element(nums.begin(), nums.end());
    if (Size == threshold) return End;

    int Result = 0;

    while (Front <= End) {
        int Middle = (Front + End) / 2;
        int Stack = 0;
        for (const auto& Element : nums) {
            Stack += (Element + Middle - 1) / Middle; // Warning! : 정수 반올림 공식 (A + B - 1) / B
            if (Stack > threshold) break;
        }

        if (Stack <= threshold) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }

    return Result;
}