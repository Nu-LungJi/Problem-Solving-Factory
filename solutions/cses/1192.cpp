// https://cses.fi/problemset/task/1192/
// Week 6 Day 2
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> Area;
int Height = 0, Width = 0;

void DFS(int i, int j) {
    Area[i][j] = '#';
        if (i - 1 >= 0 && Area[i - 1][j] == '.') DFS(i - 1, j);
        if (i + 1 < Height && Area[i + 1][j] == '.') DFS(i + 1, j);
        if (j - 1 >= 0 && Area[i][j - 1] == '.') DFS(i, j - 1);
        if (j + 1 < Width && Area[i][j + 1] == '.') DFS(i, j + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> Height >> Width;
    
    Area.resize(Height);
    for (int i = 0; i < Height; ++i) {
        std::cin >> Area[i];
    }
    
    int RoomCount = 0;
    
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (Area[i][j] == '.') {
                
                DFS(i, j);
                
                RoomCount++;
            }
        }
    }
    std::cout << RoomCount;
    
    return 0;
}
