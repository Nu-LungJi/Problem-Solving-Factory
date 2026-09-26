// https://leetcode.com/problems/isomorphic-strings/
// Week 2 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool isIsomorphic(string s, string t) {
    vector<pair<uint8_t, bool>> tAlphabetMapping(128), sAlphabetMapping(128);

    for (uint8_t i = 0; i < 128; ++i){
        pair<uint8_t, bool> Value = {i, false};
        sAlphabetMapping[i] = tAlphabetMapping[i] = Value;
    }
        
    for (size_t i = 0; i < s.size(); ++i){
        pair<uint8_t, bool>& sValue = sAlphabetMapping[s[i]];
        pair<uint8_t, bool>& tValue = tAlphabetMapping[t[i]];
        if (sValue.first == s[i] && tValue.first == t[i]){
            if (sValue.second == true || tValue.second == true){
                if (sValue.first != tValue.first) return false;
            }
            std::swap(sValue.first, tValue.first);
            tValue.second = sValue.second = true;
            continue;
        }
        else if (sValue.first == t[i] && tValue.first == s[i]) {
            continue;
        }
        return false;
    }
    return true;
}

int main()
{
    std::cout << boolalpha;
    std::cout << isIsomorphic("paper", "title") << " ";
    
    return 0;
}