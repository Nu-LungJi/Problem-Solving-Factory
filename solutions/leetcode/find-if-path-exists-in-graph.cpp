// https://leetcode.com/problems/find-if-path-exists-in-graph/
// Week 6 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> AdjustList(n);
    for (const auto& edge : edges) {
        AdjustList[edge[0]].push_back(edge[1]);
        AdjustList[edge[1]].push_back(edge[0]);
    }
        
    vector<uint8_t> Visited(n, false);
    stack<int> Stack;

    Stack.push(source);
    Visited[source] = true;

    while (!Stack.empty()) {
        int Top = Stack.top();
        Stack.pop();

        if (Top == destination) break;

        for (const auto& Elem : AdjustList[Top]) {
            if (!Visited[Elem]) {
                Visited[Elem] = true;
                Stack.push(Elem);
            }
        }
    }

    return Visited[destination];
}