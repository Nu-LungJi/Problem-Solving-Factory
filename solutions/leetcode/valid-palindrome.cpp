// https://leetcode.com/problems/valid-palindrome/
// Week 1 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int ASCII_A = 65;
const int ASCII_Z = 90;

const int ASCII_a = 97;
const int ASCII_z = 122;

const int ASCII_0 = 48;
const int ASCII_9 = 57;

const int ASCII_CaseDiff = 32;

class Solution {
public:
    bool isPalindrome(string s) {
        string ConvertedString = "";
        for (const auto& Element : s) {
            if (Element >= ASCII_A && Element <= ASCII_Z){
                ConvertedString += (Element + ASCII_CaseDiff);
            }
            else if ((Element >= ASCII_a && Element <= ASCII_z) ||
            (Element >= ASCII_0 && Element <= ASCII_9)){
                ConvertedString += Element;
            }
        }

        int Size = ConvertedString.size();

        for (int i = 0; i < Size / 2; ++i){
            if (ConvertedString[i] != ConvertedString[Size - 1 - i]) 
                return false;
        }
        return true;
    }
};

int main() {
    Solution S;
    std::cout << boolalpha;
    std::cout << S.isPalindrome("   fly me   to   the moon  ");
    return 0;
}
