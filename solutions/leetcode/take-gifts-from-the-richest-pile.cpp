// https://leetcode.com/problems/take-gifts-from-the-richest-pile/
// Week 2 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;


long long pickGifts(vector<int>& gifts, int k) {
    priority_queue<int> PQ;
    for (const auto& Element : gifts){
        PQ.emplace(Element);
    }

    while(k--){
        int Element = PQ.top();
        PQ.pop();
        PQ.emplace(sqrt(Element));
    }

    long long Count = 0;
    size_t Size = PQ.size();
    for (size_t i = 0; i < Size; ++i){
        Count += PQ.top();
        PQ.pop();
    }

    return Count;
}

int main() {
    vector<int> Input = {25,64,9,4,100};
    std::cout << pickGifts(Input, 4);
    return 0;
}