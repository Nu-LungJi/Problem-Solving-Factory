// https://leetcode.com/problems/find-the-highest-altitude/
// Week 4 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int largestAltitude(vector<int>& gain) {
    int MaxHeight = 0, PastPrefix = 0;
    for (const auto& Element : gain) {
        PastPrefix = Element + PastPrefix;
        MaxHeight = std::max(PastPrefix, MaxHeight);
    }
    return MaxHeight;
}