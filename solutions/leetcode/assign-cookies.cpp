// https://leetcode.com/problems/assign-cookies/
// Week 5 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {
    int ChildrenCount = static_cast<int>(g.size());
    int CookieCount = static_cast<int>(s.size());

    if (ChildrenCount == 0 || CookieCount == 0) return 0;

    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());
        
    int ChildrenIndex = 0, CookieIndex = 0, Result = 0;
    while (ChildrenIndex < ChildrenCount) {
        if (g[ChildrenIndex] <= s[CookieIndex]) {
            ChildrenIndex++;
            CookieIndex++;
            Result++;
        }
        else {
            CookieIndex++;
        }
        if (CookieIndex == CookieCount) break;
    }

    return Result;
}