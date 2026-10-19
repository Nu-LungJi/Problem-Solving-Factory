// https://school.programmers.co.kr/learn/courses/30/lessons/43238
// Week 5 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
    int Size = static_cast<int>(times.size());
    if (Size == 1) return static_cast<long long>(times[0]) * static_cast<long long>(n);
    
    int MaxValue = *std::max_element(times.begin(), times.end());
    long long Front = 1, Back = static_cast<long long>(MaxValue) * static_cast<long long>(n), Result = 0;
    
    while (Front <= Back) {
        long long Middle = (Front + Back) / 2, Stack = 0;
        for (const auto& time : times) {
            Stack += Middle / static_cast<long long>(time);
            if (Stack > n) break;
        }
        
        if (Stack >= n) {
            Result = Middle;
            Back = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    
    return Result;
}