// https://leetcode.com/problems/non-overlapping-intervals/
// Week 5 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool Compare(vector<int>& Front, vector<int>& End) {
        return Front[1] < End[1];
    }
class Solution {
public:
    
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int Size = static_cast<int>(intervals.size());
        std::sort(intervals.begin(), intervals.end(), Compare);

        if (Size == 1) return 0;

        int Result = 100000;
        int CurrentIndex = 0;
        while (true) {
            int RemoveCount = 0;
            vector<int> Current = intervals[CurrentIndex];
            if (CurrentIndex++ != 0 && Current[0] >= intervals.front()[0]) break;
            for (int i = 1; i < Size; ++i) {
                if (Current[1] > intervals[i][0]) {
                    RemoveCount++;
                }
                else {
                    Current = intervals[i];
                }
            }

            Result = std::min(Result, RemoveCount);
        }
        

        return Result;
    }
};