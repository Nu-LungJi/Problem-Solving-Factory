// https://school.programmers.co.kr/learn/courses/30/lessons/1844
// Week 6 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include<vector>
#include<queue>
using namespace std;

pair<int, int> ds[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int Height, Width, RouteCounter = 0;
int BFS(vector<vector<int>>& maps) {
    queue<pair<int, int>> Queue;
    Queue.push({0, 0});
    
    while (!Queue.empty()) {
        auto [x, y] = Queue.front();
        Queue.pop();
        
        if (x == Height - 1 && y == Width - 1) {
            return maps[x][y];
        }
        int Size = static_cast<int>(Queue.size());
        for (int i = 0; i < 4; ++i) {
            int X = x + ds[i].first;
            int Y = y + ds[i].second;
            
            if (X >= 0 && Y >= 0 && X < Height && Y < Width && maps[X][Y] == 1){
                maps[X][Y] = maps[x][y] + 1;
                Queue.push({X, Y});
            }
        
        }
    }
    
    return -1;
}

int solution(vector<vector<int>> maps) {
    if (maps.empty()) return 0;
    Height = static_cast<int>(maps.size());
    Width = static_cast<int>(maps[0].size());
    
    return BFS(maps);
}