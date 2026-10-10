// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Week 4 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int CurFront = 0, CurBack = 0;
        int Size = static_cast<int>(s.size());
        if (Size == 1) return 1;
        vector<int> Alphabet(128, 0);

        int Length = 0, MaxLength = 0;
        while (CurFront < Size) {
            if (Alphabet[s[CurBack]] > 0){
                CurBack = ++CurFront;
                Length = 0;
                for (auto& Elem : Alphabet) Elem = 0;

                continue;
            }
            MaxLength = std::max(MaxLength, ++Length);
            Alphabet[s[CurBack++]]++;

            if (CurBack == Size) {
                CurBack = ++CurFront;
                Length = 0;
                for (auto& Elem : Alphabet) Elem = 0;
            }
        }

        return MaxLength;
    }
};