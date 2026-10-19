// https://cses.fi/problemset/task/1629/
// Week 5 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int MovieCount = 0;
    std::cin >> MovieCount;
    
    std::vector<std::pair<int, int>> MovieInfo(MovieCount);
    for (int i = 0; i < MovieCount; ++i) std::cin >> MovieInfo[i].first >> MovieInfo[i].second;
    
    std::sort(MovieInfo.begin(), MovieInfo.end(), [](const std::pair<int, int>& Front, const std::pair<int, int>& Back) {
        if (Front.second == Back.second) return Front.first < Back.first;
        return Front.second < Back.second;
    });
    
    int LastEnd = 0, Result = 0;
    for (int i = 0; i < MovieCount; ++i) {
        if (LastEnd <= MovieInfo[i].first) {
            LastEnd = MovieInfo[i].second;
            Result++;
        }
    }
    std::cout << Result;
    return 0;
}
