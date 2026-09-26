// https://leetcode.com/problems/word-pattern/
// Week 2 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool wordPattern(string pattern, string s) {
    unordered_map<string, string> Container;
    int Count = 0;
    for (size_t t = 0; t < s.size(); ++t){
        if (s[t] == 32 || t == s.size() - 1)  Count++;
    }
    if (pattern.size() != Count) return false;
    int WordIndex = 0;

    for (size_t i = 0; i < pattern.size(); ++i){
        string Word = "";
        for (size_t t = WordIndex; t < s.size(); ++t){
            if (s[t] == 32) { 
                WordIndex = t + 1;
                break;
            }
            Word += s[t];
            WordIndex = t;
        }

        if (!Container.empty()){
            string Key = std::string(1, pattern[i]);
            for (const auto& Elem : Container){
                bool First = Elem.first == Key;
                bool Second = Elem.second == Word;
                if ((!First && Second) || (First && !Second)) return false;
            }
        }
        Container.insert({std::string(1, pattern[i]), Word});
    }

    return true;
}

int main()
{
    std::cout << boolalpha;
    std::cout << wordPattern("abba", "dog cat cat fish");
    return 0;
}