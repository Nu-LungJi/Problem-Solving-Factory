// https://cses.fi/problemset/task/1630/
// Week 5 Day 6
#include <iostream>
#include <vector>
#include <algorithm>

struct Task
{
    long long TaskTime;
    long long DeadLine;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int TaskCount = 0;
    std::cin >> TaskCount;
    
    std::vector<Task> Tasks(TaskCount);
    long long Total_DeadLine = 0;
    for (int i = 0; i < TaskCount; ++i) {
        std::cin >> Tasks[i].TaskTime >> Tasks[i].DeadLine;
        Total_DeadLine += Tasks[i].DeadLine;
    } 
    
    std::sort(Tasks.begin(), Tasks.end(), [](const Task& a, const Task& b) {
        return a.TaskTime < b.TaskTime;
    });
    
    long long Total_TaskTime = 0, Result = 0, Sum = 0;
    for (int i = 0; i < TaskCount; ++i) {
        Total_TaskTime += Tasks[i].TaskTime;
        Sum += Total_TaskTime;
    }
    Result = Total_DeadLine - Sum;
    std::cout << Result;
    
    return 0;
}