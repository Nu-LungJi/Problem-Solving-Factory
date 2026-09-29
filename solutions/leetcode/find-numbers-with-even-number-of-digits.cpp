// https://leetcode.com/problems/find-numbers-with-even-number-of-digits/
// Week 3 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int findNumbers(vector<int>& nums) {
    int Count = 0;
    for (auto& Element : nums) {
        int Length = 1;
        while (Element /= 10) {
            Length++;
        }
        if (Length%2 == 0) Count++;
    }
    return Count;
}

int main() {
    vector<int> Input = { 555, 901, 482, 1771 };
    std::cout << findNumbers(Input);
    return 0;
}