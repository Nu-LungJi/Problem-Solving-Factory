// https://leetcode.com/problems/fizz-buzz/
// Week 1 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int ASCII_0 = 48;
class Solution {
public:
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
};


int main()
{
    Solution S;
    const auto& FizzBuzz = S.fizzBuzz(100);
    for (const auto& Element : FizzBuzz)
    {
        std::cout << Element << " ";
    }
    
    return 0;
}