// https://cses.fi/problemset/task/1674/
// Week 7 Day 2
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> Graph;
std::vector<int> SubTree_Size;

int CountNumb(int u) {
    int count = 0;
    for (int v : Graph[u]) {
        count += CountNumb(v) + 1;
    }
    SubTree_Size[u] = count;
    
    return SubTree_Size[u];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);  
    int EmployeeNumb;
    std::cin >> EmployeeNumb;
    
    Graph.resize(EmployeeNumb + 1);
    SubTree_Size.resize(EmployeeNumb + 1);
    
    for (int i = 2; i <= EmployeeNumb; ++i) {
        int Relation;
        std::cin >> Relation;
        Graph[Relation].push_back(i);
    }
    
    CountNumb(1);
    
    for (int i = 1; i <= EmployeeNumb; ++i) {
        std::cout << SubTree_Size[i] << " ";
    }
    std::cout << "\n";
    
    return 0;
}
