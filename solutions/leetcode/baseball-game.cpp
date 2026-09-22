// https://leetcode.com/problems/baseball-game/
// Week 2 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int calPoints(vector<string>& operations) {
    vector<int> Result;
    for (const auto& Element : operations){
        if (Element == "C")  {
            Result.pop_back();
            continue;
        }
        else if (Element == "D") {
            Result.push_back(Result.back() * 2);
        }
        else if (Element == "+") {
            Result.push_back(Result[Result.size() - 2] + Result.back());
        }
        else {
            Result.push_back(std::stoi(Element));
        }
    }

    int sum = 0;
    for (const auto& Elem : Result){
        sum += Elem;
    }
    return sum;   
}

int main()
{
    vector<string> Input = {"5", "2", "C", "D", "+" };
    std::cout << calPoints(Input);
    return 0;
}