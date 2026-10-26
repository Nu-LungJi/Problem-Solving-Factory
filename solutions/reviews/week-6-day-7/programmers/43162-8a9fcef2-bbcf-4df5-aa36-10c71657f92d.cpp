// https://school.programmers.co.kr/learn/courses/30/lessons/43162
// Week 6 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <vector>
#include <queue>
using namespace std;
vector<bool> Visited;

void DFS(int CurVer, int VerCount, vector<vector<int>>& computers) {
    Visited[CurVer] = true;
    
    for (int i = 0; i < VerCount; ++i) {
        if (computers[CurVer][i] == 1 && !Visited[i]) {
            DFS(i, VerCount, computers);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int Size = static_cast<int>(computers.size());
    
    int NetworkCount = 0;
    Visited.resize(n, false);
    for (int i = 0; i < n; ++i) {
        if (!Visited[i]) {
            DFS(i, n, computers);
            NetworkCount++;
        }
    }
    return NetworkCount;
}