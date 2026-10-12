// https://cses.fi/problemset/task/1068/
// Week 4 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long n = 0;
    std::cin >> n;
    
    while (n != 1) {
        std::cout << n << " ";
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
    }
    std::cout << n;

    return 0;
}

