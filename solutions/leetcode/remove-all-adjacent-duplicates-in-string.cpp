// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
// Week 2 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string removeDuplicates(string s) {
    for (size_t i = 1; i < s.size(); ++i){
        if (s[i] == s[i - 1]){
            s.erase(i, 1);
            s.erase(i - 1, 1);
            i = 0;
        }
    }

    return s;
}
// cost 가 너무 많이 들어가는 코드라서 점검 필요

int main()
{
    std::cout << removeDuplicates("azxxzy");
    return 0;
}
