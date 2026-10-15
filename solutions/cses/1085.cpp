// https://cses.fi/problemset/task/1085/
// Week 5 Day 3
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int ArrayCount = 0, PartArrayCount = 0;
    std::cin >> ArrayCount >> PartArrayCount;
    
    std::vector<long long> Array(ArrayCount);
    for (int i = 0; i < ArrayCount; ++i) std::cin >> Array[i];
    
    long long Front = *std::max_element(Array.begin(), Array.end());
    long long End = std::accumulate(Array.begin(), Array.end(), 0LL);
    
    if (ArrayCount == PartArrayCount) {
        std::cout << Front;
        return 0;
    }
    if (PartArrayCount == 1) {
        std::cout << End;
        return 0;
    }
    long long  Result = 0;
    
    while (Front <= End) {
        long long Middle = (Front + End) / 2;
        long long Prefix = 0, SliceCount = 1;
        for (int i = 0; i < ArrayCount; ++i) {
            if (Prefix + Array[i]> Middle) {
                Prefix = 0;
                SliceCount++;
            }
            Prefix += Array[i];
            if (SliceCount > PartArrayCount) break;
        }
        
        if (SliceCount <= PartArrayCount) {
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
