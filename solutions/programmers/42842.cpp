// https://school.programmers.co.kr/learn/courses/30/lessons/42842
// Week 3 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> solution(int brown, int yellow) {
    int TileRow = 3, TileCol = 0;
    vector<int> Result;
    int WholeTile = brown + yellow;
    while (true) {
        if (WholeTile % TileRow == 0){
            TileCol = WholeTile / TileRow;
            if (yellow == (TileRow - 2) * (TileCol - 2)){
                Result.emplace_back(TileCol);
                Result.emplace_back(TileRow);

                break;
            }
        }
        TileRow++;
    }
    
    return Result;
}

int main() {
    auto Result = solution(8, 6);
    for (const auto& Element : Result) {
        std::cout << Element << " ";
    }
    return 0;
}