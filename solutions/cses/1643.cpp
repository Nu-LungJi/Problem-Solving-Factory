// https://cses.fi/problemset/task/1643/
// Week 4 Day 6
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ArrayCount = 0;
    std::cin >> ArrayCount;

    std::vector<long long> Array(ArrayCount, 0);
    for (int i = 0; i < ArrayCount; ++i) std::cin >> Array[i];
    
    long long CurSum = 0, PrefixMin = 0, PrefixMax = -1000000000;
    for (int i = 0; i < ArrayCount; ++i) {
        PrefixMin = std::min(PrefixMin, CurSum);
        CurSum += Array[i];
        PrefixMax = std::max(PrefixMax, CurSum - PrefixMin);
    }
    
    std::cout << PrefixMax;
    return 0;
}
