// https://cses.fi/problemset/task/1660/
// Week 4 Day 5
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ArraySize = 0, TargetValue = 0;
    std::cin >> ArraySize >> TargetValue;
    
    int LoopSize = ArraySize;
    
    std::vector<int> Array;
    int Element = 0;
    while (LoopSize-- && std::cin >> Element) {
        Array.push_back(Element);
    }
    
    int CurFront = 0, CurBack = 0, Result = 0;
    int Sum = 0;
    
    while (CurBack < ArraySize) {
        Sum += Array[CurBack];
        CurBack++;

        while (Sum > TargetValue && CurFront < ArraySize) {
            Sum -= Array[CurFront];
            CurFront++;
        }

        if (Sum == TargetValue) {
            Result++;
        }
    }
    
    std::cout << Result;
    
    return 0;
}
