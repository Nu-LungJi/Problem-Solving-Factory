// https://leetcode.com/problems/length-of-last-word/
// Week 1 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int Count = 0, PrevCount = 0;
        for (const auto& Char : s){
            if (Char != 32) {
                PrevCount = ++Count;
            }
            else if (Count > 0){
                Count = 0;
            }
        }

        return Count > 0 ? Count : PrevCount;
    }
};

int main() {
    Solution S;
    std::cout << S.lengthOfLastWord("   fly me   to   the moon  ");
    return 0;
}