// https://cses.fi/problemset/task/1083/
// Week 4 Day 7
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ArrayCount = 0;
    std::cin >> ArrayCount;
    
    std::vector<uint8_t> Array(ArrayCount, 0);
    
    int Element = 0;
    while (std::cin >> Element) {
        Array[Element - 1] = 1;
    }
    
    for (int i = 0; i < ArrayCount; ++i) {
        if (Array[i] == 0) std::cout << i + 1 << " ";
    }
    
    return 0;
}
