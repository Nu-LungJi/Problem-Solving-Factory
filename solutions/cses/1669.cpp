// https://cses.fi/problemset/task/1669/
// Week 7 Day 6
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> Graph;
std::vector<bool> visited;
std::vector<int> Parent;

int Start = -1, End = -1;


bool DFS(int u, int parent) {
    visited[u] = true;
    Parent[u] = parent;
    
    for (int v : Graph[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            Start = v;
            End = u;
            return true;
        }
        
        if (DFS(v, u)) return true;
    }
    
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int CityCount, RoadCount;
    std::cin >> CityCount >> RoadCount;
    
    visited.resize(CityCount + 1, false);
    Graph.resize(CityCount + 1);
    Parent.resize(CityCount + 1, 0);
    for (int i = 0; i < RoadCount; ++i) {
        int u, v;
        std::cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    
    for (int i = 1; i <= CityCount; ++i) {
        if (!visited[i] && DFS(i, 0)) break;
    }
    
    if (Start == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    
    std::vector<int> cycle;
    cycle.push_back(Start);

    for (int curr = End; curr != Start; curr = Parent[curr]) {
        cycle.push_back(curr);
    }
    cycle.push_back(Start);

    reverse(cycle.begin(), cycle.end());

    std::cout << cycle.size() << "\n";
    for (int node : cycle) {
        std::cout << node << " ";
    }
    std::cout << "\n";
    
    return 0;
}
