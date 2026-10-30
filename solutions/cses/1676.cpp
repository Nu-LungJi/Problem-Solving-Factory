// https://cses.fi/problemset/task/1676/
// Week 7 Day 4
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> Cities;
std::vector<int> Group;
int Numb_Cities;  
int Max_City_size;
int find(int i) {
    if (Cities[i] == i) return i;
    return Cities[i] = find(Cities[i]);
}

bool Union(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    
    if (root_i != root_j) {
        Cities[root_i] = root_j;
        Group[root_j] += Group[root_i];
        
        Max_City_size = std::max(Max_City_size, Group[root_j]);
        
        Numb_Cities--;
        return true;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int CityCount, RoadCount;
    std::cin >> CityCount >> RoadCount;
    
    std::vector<std::vector<int>> RoadList;
    for (int i = 0; i < RoadCount; ++i) {
        std::vector<int> s(2);
        std::cin >> s[0] >> s[1];
        RoadList.push_back(s);
    }
    Cities.resize(CityCount + 1);
    Group.resize(CityCount + 1, 1);
    for (int i = 1; i <= CityCount; ++i) {
        Cities[i] = i;
    }
    Numb_Cities = CityCount;
    Max_City_size = 1;
    
    for (const auto& Edge : RoadList) {
        int u = Edge[0];
        int v = Edge[1];
        
        Union(u, v);
        
        std::cout << Numb_Cities << " " << Max_City_size << "\n";
    }
    return 0;
}
