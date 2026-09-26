// https://leetcode.com/problems/last-stone-weight/
// Week 2 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;


int lastStoneWeight(vector<int>& stones) {
    if (stones.size() <= 1) return stones.front();

    priority_queue<int> PQ;
    for (const auto& Element : stones){
        PQ.emplace(Element);
    }

    while (PQ.size() > 1){
        int Y = PQ.top();
        PQ.pop();
        int X = PQ.top();
        PQ.pop();

        int Result = Y - X;
        if (Result != 0){
            PQ.emplace(Result);
        }
    }
    if (PQ.size() == 0) return 0;
    return PQ.top();
}

int main()  {
    vector<int> Input = {2,7,4,1,8,1};
    std::cout << lastStoneWeight(Input) << " ";
    
    return 0;
}