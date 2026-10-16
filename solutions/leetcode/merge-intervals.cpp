// https://leetcode.com/problems/merge-intervals/
// Week 5 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int Size = static_cast<int>(intervals.size());
    if (Size == 1) return intervals;
        
    std::sort(intervals.begin(), intervals.end());
    vector<vector<int>> Result;

    Result.push_back(intervals[0]);

    for (int i = 1; i < Size; ++i) {
        auto ResultBack = Result.back();
        if (ResultBack[1] >= intervals[i][0]) {
            vector<int> Temp = { ResultBack[0], std::max(intervals[i][1], ResultBack[1])};
            Result.pop_back();
            Result.push_back(Temp);
        }
        else {
            Result.push_back(intervals[i]);
        }
    }

    return Result;
}