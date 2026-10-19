// https://cses.fi/problemset/task/1630/
// Week 5 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int TaskCount = 0;
    std::cin >> TaskCount;
    
    std::vector<std::pair<long long, long long>> Tasks(TaskCount);
    long long Total_Deadline = 0, Total_TaskTime = 0, Sum = 0;
    for (int i = 0; i < TaskCount; ++i) {
        std::cin >> Tasks[i].first >> Tasks[i].second;
        Total_Deadline += Tasks[i].second;
    }
    
    std::sort(Tasks.begin(), Tasks.end(), [](const std::pair<long long, long long>& a, const std::pair<long long, long long>& b) {
        return a.first < b.first;
    });
    
    for (int i = 0; i < TaskCount; ++i) {
        Total_TaskTime += Tasks[i].first;
        Sum += Total_TaskTime;
    }
    std::cout << Total_Deadline - Sum;
    return 0;
}
