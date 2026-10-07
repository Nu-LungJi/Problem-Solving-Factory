// https://cses.fi/problemset/task/1652/
// Week 4 Day 2
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int GridSize = 0, OpsCount = 0;
    std::cin >> GridSize >> OpsCount;
    
    std::vector<std::vector<int>> ForestGrid;
    
    std::string GridRow;
    int LoopCount = GridSize;
    while (LoopCount-- && std::cin >> GridRow) {
        std::vector<int> GridRowVec;
        for (const auto& Element : GridRow) {
            if (Element == '.') GridRowVec.push_back(0);
            else GridRowVec.push_back(1);
        }
        ForestGrid.push_back(GridRowVec);
    }
    
    for (int i = 0; i < GridSize; ++i) {
        for (int j = 1; j < GridSize; ++j) {
            ForestGrid[i][j] += ForestGrid[i][j - 1];
        }
    }
    
    for (int i = 1; i < GridSize; ++i) {
        for (int j = 0; j < GridSize; ++j) {
            ForestGrid[i][j] += ForestGrid[i - 1][j];
        }
    }
    
    int Row1, Col1, Row2, Col2;
    while (OpsCount-- && std::cin >> Row1 >> Col1 >> Row2 >> Col2) {
        int Result = ForestGrid[Row2 - 1][Col2 - 1];
        if (Row1 > 1 && Col1 > 1) {
            Result -= ForestGrid[Row2 - 1][Col1 - 2];
            Result -= ForestGrid[Row1 - 2][Col2 - 1];
            Result += ForestGrid[Row1 - 2][Col1 - 2];
        }
        else if (Row1 > 1) {
            Result -= ForestGrid[Row1 - 2][Col2 - 1];
        }
        else if (Col1 > 1) {
            Result -= ForestGrid[Row2 - 1][Col1 - 2];
        }
        
        std::cout << Result << "\n";
    }
    
    return 0;
}
