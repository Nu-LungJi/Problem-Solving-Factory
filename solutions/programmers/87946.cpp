// https://school.programmers.co.kr/learn/courses/30/lessons/87946
// Week 3 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <vector>
#include <array>

using namespace std;
int MAX_DUNGEON_COUNT = 0;
array<bool, 8> CheckList{false};
void Recurv(vector<vector<int>>& dungeons, int& MaxDungeon, int& Current, int Start, int Count) {
    if (Count == 0){
        MAX_DUNGEON_COUNT = std::max(MAX_DUNGEON_COUNT, MaxDungeon);
        return ;
    }
    
    for (int i = Start; i < dungeons.size(); ++i) {
        if (Current < dungeons[i][0] && !CheckList[i]) continue;
        Current -= dungeons[i][1];  MaxDungeon += 1;
        CheckList[i] = true;
        Recurv(dungeons, MaxDungeon, Current, 0, Count - 1);
        CheckList[i] = false;
        Current += dungeons[i][1];  MaxDungeon -= 1;
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    for (int i = 1; i <= dungeons.size(); ++i){
        int MaxDungeon = 0;
        Recurv(dungeons, MaxDungeon, k, 0, i);
    }
    
    return MAX_DUNGEON_COUNT;
}