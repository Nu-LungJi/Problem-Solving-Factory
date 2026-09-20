// https://leetcode.com/problems/roman-to-integer/
// Week 1 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const unsigned int ASCII_M = 77;
const unsigned int ASCII_C = 67;
const unsigned int ASCII_D = 68;
const unsigned int ASCII_X = 88;
const unsigned int ASCII_L = 76;
const unsigned int ASCII_I = 73;
const unsigned int ASCII_V = 86;

class Solution {
public:
    int romanToInt(string s) {
        int Result = 0;
        int CurrentIndex = 0;

        while(s[CurrentIndex] == ASCII_M){
            Result += 1000;
            CurrentIndex++;
        }

        while(s[CurrentIndex] == ASCII_D){
            Result += 500;
            CurrentIndex++;
        }

        while(s[CurrentIndex] == ASCII_C){
            if (s[CurrentIndex + 1] == ASCII_D){
                CurrentIndex += 2;
                Result += 400;
                continue;
            }
            else if (s[CurrentIndex + 1] == ASCII_M){
                CurrentIndex += 2;
                Result += 900;
                continue;
            }
            Result += 100;
            CurrentIndex++;
        }

        while(s[CurrentIndex] == ASCII_L){
            Result += 50;
            CurrentIndex++;
        }

        while(s[CurrentIndex] == ASCII_X){
            if (s[CurrentIndex + 1] == ASCII_L){
                CurrentIndex += 2;
                Result += 40;
                continue;
            }
            else if (s[CurrentIndex + 1] == ASCII_C){
                CurrentIndex += 2;
                Result += 90;
                continue;
            }
            Result += 10;
            CurrentIndex++;
        }
        while(s[CurrentIndex] == ASCII_V){
            Result += 5;
            CurrentIndex++;
        }

        while(s[CurrentIndex] == ASCII_I){
            if (s[CurrentIndex + 1] == ASCII_V){
                CurrentIndex += 2;
                Result += 4;
                continue;
            }
            else if (s[CurrentIndex + 1] == ASCII_X){
                CurrentIndex += 2;
                Result += 9;
                continue;
            }
            Result += 1;
            CurrentIndex++;
        }

        return Result;
    }
};

int main()
{
    Solution s;
    std::cout << s.romanToInt("MCMXCIV");
    return 0;
}