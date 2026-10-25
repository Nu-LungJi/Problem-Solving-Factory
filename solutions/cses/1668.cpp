// https://cses.fi/problemset/task/1668/
// Week 6 Day 6
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
int PupilNumb, ThreadNumb;
std::vector<std::vector<int>> graph;
bool BFS(std::vector<int>& TeamList) {
    std::queue<int> Queue;
    Queue.push(1);
    
    for (int i = 1; i <= PupilNumb; ++i) {
        if (TeamList[i] != 0) continue;
        
        Queue.push(i);
        TeamList[i] = 1;
        
        while (!Queue.empty()) {
            int Top = Queue.front();
            Queue.pop();
            
            for (int Next : graph[Top]) {
                if (TeamList[Next] == 0) {
                    TeamList[Next] = (TeamList[Top] == 1) ? 2 : 1;
                    Queue.push(Next);
                }
                else if (TeamList[Next] == TeamList[Top]) {
                    return false;
                }
            }
        }
    }
    
    return true;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> PupilNumb >> ThreadNumb;
    
    std::vector<int> TeamList(PupilNumb + 1, 0);
    graph.resize(PupilNumb + 1);
    for (int i = 0; i < ThreadNumb; ++i) {
        int X, Y;
        std::cin >> X >> Y;
        graph[X].push_back(Y);
        graph[Y].push_back(X);
    }
    
    if (!BFS(TeamList)) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    
    for (int i = 1; i <= PupilNumb; ++i) {
        std::cout << TeamList[i] << " ";
    }
    
    return 0;
}
