// https://cses.fi/problemset/task/1668/
// Week 6 Day 7
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int PupilNumb, RelationShip;
std::vector<std::vector<int>> Graph;

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
            
            for (int Next : Graph[Top]) {
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
    std::cin >> PupilNumb >> RelationShip;
    
    std::vector<int> TeamList(PupilNumb + 1, 0);
    Graph.resize(PupilNumb + 1);
    for (int i = 0; i < RelationShip; ++i) {
        int X, Y;
        std::cin >> X >> Y;
        Graph[X].push_back(Y);
        Graph[Y].push_back(X);
    }
    
    if (!BFS(TeamList)) {
        std::cout << "IMPOSSIBLE" << "\n";
        return 0;
    }
    
    for (int i = 1; i <= PupilNumb; ++i) 
        std::cout << TeamList[i] << " ";
    
    return 0;
}
