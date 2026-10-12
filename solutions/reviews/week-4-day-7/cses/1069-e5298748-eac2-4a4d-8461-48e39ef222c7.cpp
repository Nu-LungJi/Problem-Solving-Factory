// https://cses.fi/problemset/task/1069/
// Week 4 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string Input;
    std::cin >> Input;
    
    int Result = 0, Count = 1;
    for (auto iter = Input.begin(); iter != Input.end();) {
        if ((*iter) == (*(iter + 1))) {
            Count++;
        }
        else {
            Result = std::max(Count, Result);
            Count = 1;
        }
        iter++;
    }
    
    std::cout << Result;
    
    return 0;
}
