// https://leetcode.com/problems/backspace-string-compare/
// Week 2 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool backspaceCompare(string s, string t) {
    string ResultS, ResultT;

    for (const auto& Element : s){
        if (Element == '#') {
            if (!ResultS.empty()) ResultS.pop_back();
        }
        else { ResultS.push_back(Element); }
    }

    for (auto& Element : t){
        if (Element == '#') {
            if (!ResultT.empty())  ResultT.pop_back();
        }
        else { ResultT.push_back(Element); }
    }

    if (ResultS == ResultT) return true;

    return false;
}

int main()
{
    std::cout << boolalpha;
    std::cout << backspaceCompare("ab##", "c#d#");
    
    return 0;
}