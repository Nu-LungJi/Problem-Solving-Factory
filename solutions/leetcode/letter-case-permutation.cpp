// https://leetcode.com/problems/letter-case-permutation/
// Week 3 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// 다시 풀어보기
constexpr int ASCII_0 = 48;
constexpr int ASCII_9 = 57;
constexpr int ASCII_A = 65;
constexpr int ASCII_a = 97;

constexpr int ASCII_CONV = 32;

class Solution {
public:
    vector<string> Result;
    void Solve(string& s, int Count) {
        if (Count == s.size()) return;

        if (s[Count] >= ASCII_A){
            s[Count] += s[Count] < ASCII_a ? ASCII_CONV : -ASCII_CONV;
            Result.emplace_back(s);
            Solve(s, Count + 1);
            s[Count] += s[Count] < ASCII_a ? ASCII_CONV : -ASCII_CONV;
        }
        Solve(s, Count + 1);
    }

    vector<string> letterCasePermutation(string s) {
        Result.emplace_back(s);
        Solve(s, 0);
        return Result;
    }
};