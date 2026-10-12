// https://leetcode.com/problems/palindrome-number/
// Week 4 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



bool isPalindrome2(int x) {
    if (x >= 0 && x < 10) return true;
    if (x < 0 || x % 10 == 0) return false;

    string X = to_string(x);

    int Size = static_cast<int>(X.size());
    for (int i = 0; i < Size / 2; ++i) {
        if (X[i] != X[Size - 1 - i]) return false;
    }
    return true;
}

bool isPalindrome(int x) {
    if (x >= 0 && x < 10) return true;
    if (x < 0 || x % 10 == 0) return false;
    int IntLength = 1;
    while (x / IntLength > 9) IntLength *= 10;

    while (IntLength > 9) {
        if (x/IntLength != x%10) return false;

        IntLength /= 10;
        x = x / 10 % IntLength;
        IntLength /= 10;
    }

    return true;
}