// https://leetcode.com/problems/valid-parentheses/
// Week 2 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool isValid(string s) {
    size_t StringSize = s.size();
    if (StringSize <= 1) return false;

    vector<int> Open;
    for (size_t i = 0; i < StringSize; ++i){
        int Close;
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            Open.emplace_back(s[i]);
            continue;
        }
        else if (s[i] == ')') Close = '(';
        else if (s[i] == ']') Close = '[';
        else if (s[i] == '}') Close = '{';

        if (!Open.empty() && Open.back() == Close){
            Open.pop_back();
            continue;
        }

        return false;
    }

    if (!Open.empty()) return false;

    return true;
}

int main()
{
    std::cout << boolalpha;
    std::cout << isValid("([])");
    
    return 0;
}