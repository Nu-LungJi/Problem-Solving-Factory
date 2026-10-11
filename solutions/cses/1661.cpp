// https://cses.fi/problemset/task/1661/
// Week 4 Day 6
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ArrayCount = 0, TargetNumb = 0;
    std::cin >> ArrayCount >> TargetNumb;
    
    std::vector<long long> Array(ArrayCount, 0);
    for (int i = 0; i < ArrayCount; ++i) std::cin >> Array[i];
    
    std::map<long long, int> PrefixHistory;
    //PrefixHistory.reserve(ArrayCount + 1);
    PrefixHistory[0] = 1;
    long long CurSum = 0, Result = 0;
    for (int i = 0; i < ArrayCount; ++i) {
        CurSum += Array[i];
        auto iter = PrefixHistory.find(CurSum - TargetNumb);
        if (iter != PrefixHistory.end()) Result += iter->second;
        PrefixHistory[CurSum]++;
    }
    
    std::cout << Result;
    
    return 0;
}
