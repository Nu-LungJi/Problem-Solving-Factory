// https://cses.fi/problemset/task/1083/
// Week 1 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    uint64_t MaxNumber = 0;
    std::cin >> MaxNumber;
    
    uint64_t Element = 0;
    std::vector<uint8_t> FlagSet(MaxNumber, false);
    
    while (std::cin >> Element && Element != 0) {
        FlagSet[Element - 1] = 1;
    }
    
    for (size_t i = 0; i < FlagSet.size(); ++i) {
        if (FlagSet[i] == 0) std::cout << i + 1 << " ";
    }
    
    return 0;
}
