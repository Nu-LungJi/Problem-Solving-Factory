// https://school.programmers.co.kr/learn/courses/30/lessons/42626
// Week 2 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> PQ;
    
    for (const auto& Element : scoville) {
        PQ.emplace(Element);
    }
    
    int Count = 0;
    
    while (PQ.top() < K && PQ.size() > 1){
        int X = PQ.top(); PQ.pop();
        int Y = PQ.top(); PQ.pop();
        
        PQ.emplace(X + (Y * 2));
        Count++;
    }
    
    if (PQ.top() < K && PQ.size() <= 1) return -1;

    return Count;
}

int main()
{
    std::cout << solution(vector<int>{1, 2, 3, 9, 10, 12}, 7);
    return 0;
}