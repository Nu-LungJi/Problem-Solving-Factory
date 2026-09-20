// https://leetcode.com/problems/number-of-1-bits/
// Week 1 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int hammingWeight(int n) {
        unsigned int Count = 0;
        
        while(n != 1){
            (n % 2 == 1) ? Count++ : Count;
            n /= 2;
        }

        return ++Count;
    }
};

int main()
{
    Solution S;
    std::cout << S.hammingWeight(2147483645);
    
    return 0;
}