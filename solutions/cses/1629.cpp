// https://cses.fi/problemset/task/1629/
// Week 5 Day 4
#include <iostream>
#include <vector>
#include <algorithm>

struct Movie {
    int start, end;
};

bool compareMovies(const Movie& a, const Movie& b) {
    if (a.end == b.end) {
        return a.start < b.start; // 종료 시간이 같다면 시작 시간이 빠른 것 우선
    }
    return a.end < b.end;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int MovieCount = 0;
    std::cin >> MovieCount;
    
    std::vector<Movie> TimeList(MovieCount);
    for (int i = 0; i < MovieCount; ++i) {
        std::cin >> TimeList[i].start >> TimeList[i].end;
    }

    std::sort(TimeList.begin(), TimeList.end(), compareMovies);
    
    int LastEnd = 0, WatchCount = 0;
    for (int i = 0; i < MovieCount; ++i) {
        if (LastEnd <= TimeList[i].start) {
            WatchCount++;
            LastEnd = TimeList[i].end;
        }
    }
    
    std::cout << WatchCount;
    
    return 0;
}
