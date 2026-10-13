// https://leetcode.com/problems/sqrtx/
// Week 5 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int mySqrt(int x) {
    if (x == 0) return x;
    int Front = 1, End = x;

    while (Front <= End) {
        int Middle = Front + (End - Front) / 2;
        if (Middle == x / Middle) return Middle;
        else if (Middle > x / Middle) {
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    return End;
}