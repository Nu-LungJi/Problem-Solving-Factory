// https://leetcode.com/problems/all-paths-from-source-to-target/
// Week 6 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void DFS(const vector<vector<int>>& graph, int CurIDX, int Target, vector<int>& CurPath, vector<vector<int>>& Result) {
    if (CurIDX == Target) {
        Result.push_back(CurPath);
        return;
    }

    for (const auto& Element : graph[CurIDX]) {
        CurPath.push_back(Element);
        DFS(graph, Element, Target, CurPath, Result);
        CurPath.pop_back();
    }
}
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    int Size = static_cast<int>(graph.size());
    vector<vector<int>> Result;
    vector<int> CurrentPath(1, 0);

    DFS(graph, 0, Size - 1, CurrentPath, Result);

    return Result;
}