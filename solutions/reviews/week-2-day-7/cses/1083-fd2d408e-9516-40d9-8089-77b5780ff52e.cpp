// https://cses.fi/problemset/task/1083/
// Week 2 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int MaxNumb = 0;
    std::cin >> MaxNumb;
    std::vector<int> Array(MaxNumb, 0);
    
    int Element = 0;
    while (std::cin >> Element) {
        Array[Element - 1] = 1;
    }
    
    for (size_t i = 0 ; i < Array.size(); ++i) {
        if (Array[i] != 1) std::cout << i + 1 << " ";
    }
    
    return 0;
}
