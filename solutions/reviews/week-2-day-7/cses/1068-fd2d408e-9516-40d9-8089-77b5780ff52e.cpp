// https://cses.fi/problemset/task/1068/
// Week 2 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned long long Value = 0;
    std::cin >> Value;
    
    while (Value != 1) {
        std::cout << Value << " ";
        if (Value % 2 == 1) Value = 3 * Value + 1;
        else Value /= 2;
    }
    std::cout << Value << " ";
    
    return 0;
}
