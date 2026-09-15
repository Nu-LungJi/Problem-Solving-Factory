// https://leetcode.com/problems/fizz-buzz/
// Week 1 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> Result;
        for (int i = 1; i <= n; ++i){
            if (i % 3 == 0 && i % 5 == 0){
                Result.emplace_back("FizzBuzz");
            }
            else if (i % 3 == 0) {
                Result.emplace_back("Fizz");
            }
            else if (i % 5 == 0) {
                Result.emplace_back("Buzz");
            }
            else {
                Result.emplace_back(to_string(i));
            }
        }

        return Result;
    }
};

int main()
{
    Solution Quest;
    auto Result = Quest.fizzBuzz(10);
    cout << "[ ";
    for (auto& Element : Result)
    {
        cout << Element << "\t";
    }
    cout << " ]";
    return 0;
}