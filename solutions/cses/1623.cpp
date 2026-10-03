// https://cses.fi/problemset/task/1623/
// Week 3 Day 5
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <numeric>
#define INT_MAX       2147483647

long long MinimumDiff = INT_MAX;
std::array<bool, 21> CheckList{false};

void Solution(std::vector<long long>& AppleList, long long& Result, int Start, int Count) {
    if (Count == 0) {
        long long OtherResult = 0;
        for (size_t i = 0; i < AppleList.size(); ++i) {
            if (CheckList[i]) continue;
            OtherResult += AppleList[i];
        }
        MinimumDiff = std::min(std::abs(Result - OtherResult), MinimumDiff);
        return;
    }
    
    for (size_t i = Start; i < AppleList.size(); ++i) {
        Result += AppleList[i];
        CheckList[i] = true;
        Solution(AppleList, Result, i + 1, Count - 1);
        CheckList[i] = false;
        Result -= AppleList[i];
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int Count = 0;
    std::cin >> Count;
    
    std::vector<long long> AppleList;
    
    int Element = 0;
    while (Count-- && std::cin >> Element) {
        AppleList.emplace_back(Element);
    }
    
    for (size_t i = 1; i <= AppleList.size(); ++i) {
        long long Diff = 0;
        Solution(AppleList, Diff, 0, i);
    }
    
    std::cout << MinimumDiff << "\n";
    
    return 0;
}
