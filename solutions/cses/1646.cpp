// https://cses.fi/problemset/task/1646/
// Week 4 Day 1
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int ArrayCount = 0, CommandCount = 0;
    std::cin >> ArrayCount >> CommandCount;
    
    long long QueryElement = 0;
    std::vector<long long> QueryArray;
    QueryArray.emplace_back(0);
    while (ArrayCount-- && std::cin >> QueryElement) {
        QueryArray.emplace_back(QueryElement + QueryArray.back());
    }
    
    int Left, Right;
    while (CommandCount-- && std::cin >> Left >> Right) {
        std::cout << QueryArray[Right] - QueryArray[Left - 1] << "\n";
    }
    
    return 0;
}
