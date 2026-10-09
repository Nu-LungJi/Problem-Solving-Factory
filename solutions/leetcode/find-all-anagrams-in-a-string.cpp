// https://leetcode.com/problems/find-all-anagrams-in-a-string/
// Week 4 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int Size = static_cast<int>(s.size());
        int EvalSize = static_cast<int>(p.size());
        vector<int> Result;

        if (Size < EvalSize) return Result;

        vector<int> pCount(26, 0);
        vector<int> sCount(26, 0);

        for (int i = 0; i < EvalSize; ++ i){
            pCount[p[i] -'a']++;
            sCount[s[i] -'a']++;
        }

        if (pCount == sCount) {
            Result.push_back(0);
        }

        for (int i = EvalSize; i < Size; ++i) {
            sCount[s[i] - 'a']++;
            --sCount[s[i - EvalSize] - 'a'];

            if (pCount == sCount) {
                Result.push_back(i - EvalSize + 1);
            }
        }

        return Result;
    }
};