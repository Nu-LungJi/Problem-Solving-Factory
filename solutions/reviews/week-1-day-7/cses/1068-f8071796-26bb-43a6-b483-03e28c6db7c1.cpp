// https://cses.fi/problemset/task/1068/
// Week 1 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned long long Element = 0;
    std::cin >> Element;
    
    while (true) {
        std::cout << Element << " ";
        if (Element == 1) break;
        Element = Element % 2 == 1 ? 3 * Element + 1 : Element / 2;
    }
    
    return 0;
}
