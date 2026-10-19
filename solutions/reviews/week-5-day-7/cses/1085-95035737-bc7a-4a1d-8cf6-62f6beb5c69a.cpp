// https://cses.fi/problemset/task/1085/
// Week 5 Day 7
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int ArrayCount = 0, SubArrDiv = 0;
    std::cin >> ArrayCount >> SubArrDiv;
    
    std::vector<long long> Array(ArrayCount);
    long long Front = 0, End = 0, Result = 0;
    for (int i = 0; i < ArrayCount; ++i) {
        std::cin >> Array[i];
        End += Array[i];
    }
    Front = *std::max_element(Array.begin(), Array.end());
    if (ArrayCount == 1)  {
        std::cout << Array[0];
        return 0;
    }
    if (SubArrDiv == 1) {
        std::cout << End;
        return 0;
    }
    
    while (Front <= End) {
        long long Middle = (Front + End) / 2, Stack = 0, ArrCount = 1;
        for (int i = 0 ; i < ArrayCount; ++i) {
            if (Stack + Array[i] > Middle) {
                ArrCount++;
                Stack = 0;
            }
            Stack += Array[i];
            if (ArrCount > SubArrDiv) break;
        }
        
        if (ArrCount <= SubArrDiv) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    
    std::cout << Result;
    
    return 0;
}
