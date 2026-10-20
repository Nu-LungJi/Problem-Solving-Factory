// https://cses.fi/problemset/task/1666/
// Week 6 Day 1
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int CityCount = 0, RoadCount = 0;
    std::cin >> CityCount >> RoadCount;
    
    std::vector<std::vector<int>> AdjustGraph(CityCount + 1);
    for (int i = 0; i < RoadCount; ++i) {
        int CityA, CityB;
        std::cin >> CityA >> CityB;
        AdjustGraph[CityA].push_back({CityB});
        AdjustGraph[CityB].push_back({CityA});
    }
    
    std::vector<unsigned char> Visited(CityCount + 1, false);
    std::vector<int> CapitalCity;
    
    for (int i = 1; i <= CityCount; ++i) {
        if (!Visited[i]) {
            
            CapitalCity.push_back(i);
            Visited[i] = true;
            std::stack<int> Stack;
            Stack.push(i);
            
            while (!Stack.empty()) {
                int Top = Stack.top();
                Stack.pop();
        
                for (const auto& Elem : AdjustGraph[Top]) {
                    if (!Visited[Elem]) {
                        Visited[Elem] = true;
                        Stack.push(Elem);
                    }
                }
            }
        }
    }
    
    int IslandCount = static_cast<int>(CapitalCity.size());
    std::cout << IslandCount - 1 << "\n";
    for (int i = 1; i < IslandCount; i++) {
        std::cout << CapitalCity[i - 1] << " " << CapitalCity[i] << "\n";
    }
    
    
    return 0;
}
