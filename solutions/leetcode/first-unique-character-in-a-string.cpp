// https://leetcode.com/problems/first-unique-character-in-a-string/
// Week 1 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        if (s.size() == 1) return 0;
        std::array<bool, 26> CachedList = {false};
        int Index = -1;

        for (uint32_t i = 0; i < s.size(); ++i){
            int AlphabetIndex = s[i] - 97; 
            if (CachedList[AlphabetIndex]) continue;

            Index = i;

            for (uint32_t j = i + 1; j < s.size(); ++j){
                if (s[i] == s[j]) {
                    CachedList[AlphabetIndex] = true;
                    Index = -1;
                    break;
                }
            }

            if (Index >= 0) return Index;
        }

        return Index;
    }
};

int main()
{
    Solution S;
    std::cout << S.firstUniqChar("leetcode");
    
    return 0;
}