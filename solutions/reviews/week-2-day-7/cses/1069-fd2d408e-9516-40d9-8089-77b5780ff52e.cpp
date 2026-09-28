// https://cses.fi/problemset/task/1069/
// Week 2 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string DNA;
    std::cin >> DNA;
    
    int Max = 0, Count = 1;
    for (size_t i = 1; i < DNA.size();++i) {
        if (DNA[i - 1] != DNA[i]) {
            Max = std::max(Max, Count);
            Count = 1;
            continue;
        }
        Count++;
    }
    Max = std::max(Max, Count);
    std::cout << Max;
    
    return 0;
}
