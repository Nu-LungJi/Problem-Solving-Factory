// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
// Week 5 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int minDays(vector<int>& bloomDay, int m, int k) {
    long long Size = static_cast<long long>(bloomDay.size());
    if (Size < static_cast<long long>(m) * static_cast<long long>(k)) return -1;

    if (k == 1) {
        std::sort(bloomDay.begin(), bloomDay.end());
        return bloomDay[m - 1];
    }

    long long Front = *std::min_element(bloomDay.begin(), bloomDay.end());
    long long End = *std::max_element(bloomDay.begin(), bloomDay.end());

    long long Result = 0;
    while (Front <= End) {
        long long Middle = (Front + End) / 2;
        int Stack = 0, Flowers = 0;
        for (int i = 0 ; i < Size; ++i) {
            if (bloomDay[i] <= Middle) Stack++;
            else Stack = 0;

            if (Stack == k) {
                Stack = 0;
                Flowers++;
            }
            if (Flowers > m) break;
        }

        if (Flowers >= m){
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }

    return Result;
}