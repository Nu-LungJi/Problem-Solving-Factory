// https://cses.fi/problemset/task/1620/
// Week 5 Day 2
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long MachineCount = 0, ProductCount = 0;
    std::cin >> MachineCount >> ProductCount;
    
    std::vector<long long> MachineTime(MachineCount);
    for (int i = 0; i < MachineCount; ++i) std::cin >> MachineTime[i];
    
    long long Front = 1;
    long long End = *std::max_element(MachineTime.begin(), MachineTime.end()) * ProductCount, Result = 0;
    
    if (MachineCount == 1) {
        std::cout << End;
        return 0;
    }
    
    while (Front <= End) {
        long long Middle = (Front + End) / 2;
        
        long long Product = 0;
        for (const auto& Element : MachineTime) {
            Product += Middle / Element;
            if (Product > ProductCount) break;
        }
        
        if (ProductCount <= Product) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    
    std::cout << Result;
    
    return 0;
}
