// https://leetcode.com/problems/fizz-buzz/
// Week 2 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> fizzBuzz(int n) {

    vector<string> StringList;
    for (int i = 1; i <= n; ++i){
        string Element = "";
        if      (i % 15 == 0)    { Element = "FizzBuzz"; }
        else if (i % 3 == 0)     { Element = "Fizz";     }
        else if (i % 5 == 0)     { Element = "Buzz";     }
        else                { Element = std::to_string(i); }

        StringList.emplace_back(Element);
    }

    return StringList;
}

const int ASCII_0 = 48;
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> Result(n);

        for (size_t i = 1; i < n + 1; ++i){
            string Element;
            if (i % 15 == 0) Element = "FizzBuzz";
            else if (i % 3 == 0) Element = "Fizz";
            else if (i % 5 == 0) Element = "Buzz";
            else Element = std::to_string(i);

            Result[i - 1] = Element;
        }
        
        return Result;
    }
};