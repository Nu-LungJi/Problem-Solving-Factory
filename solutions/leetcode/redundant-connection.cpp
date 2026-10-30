// https://leetcode.com/problems/redundant-connection/
// Week 7 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

std::vector<int> NodeList;

int find(int i) {
    if (NodeList[i] == i) return i;
    return NodeList[i] = find(NodeList[i]); 
}

bool unionSet(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
        
    if (root_i != root_j) {
        NodeList[root_i] = root_j;
        return true;
    }
    return false;
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int Size = static_cast<int>(edges.size());
    NodeList.resize(Size + 1);

    for (int i = 1; i <= Size; ++i) NodeList[i] = i;

    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
                
        if (!unionSet(u, v)) return edge;
    }

    return {};
}