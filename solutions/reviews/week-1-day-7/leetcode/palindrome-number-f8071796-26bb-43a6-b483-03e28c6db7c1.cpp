// https://leetcode.com/problems/palindrome-number/
// Week 1 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x < 10) return true;

        int len = 1;
        while(x/len > 9) len *= 10;

        while(len > 1){
            if (x/len != x%10) return false;

            len /= 10;
            x = x / 10 % len;
            len /= 10;
        }

        return true;        
    }
};

int main()
{
    Solution S;
    
    std::cout << boolalpha;
    std::cout << S.isPalindrome(123321);
    
    return 0;
}