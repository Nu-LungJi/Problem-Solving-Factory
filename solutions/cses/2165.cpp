// https://cses.fi/problemset/task/2165/
// Week 3 Day 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

void Hanoi(int MoveDiskCount, int From, int To, int Aux) {
    if (MoveDiskCount == 0) return;
    Hanoi(MoveDiskCount - 1, From, Aux, To);        // N개의 원판 중에 제일 하단 원판을 제외한 위에 있는 모든 원판을 보조Tower로 이동
    std::cout << From + 1 << " " << To + 1 << "\n";         // N개의 원판 중에 제일 하단 원판을 목적지Tower로 이동
    Hanoi(MoveDiskCount - 1, Aux, To, From);       // 제일 하단 원판을 제외한 나머지 N - 1 원판을 목적지Tower로 이동.
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int DiskCount = 0;
    std::cin >> DiskCount;
    
    std::cout << (1 << DiskCount) - 1 << "\n";
    
    Hanoi(DiskCount, 0, 2, 1);
    
    return 0;
}