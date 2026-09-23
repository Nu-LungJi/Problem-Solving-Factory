// https://school.programmers.co.kr/learn/courses/30/lessons/42587
// Week 2 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> priorities, int location) {
    int CurrentFront = 0, LocationCount = 1;
    int CaseSize = priorities.size();
    
    while(true){
        int MaxValue = 0;
        for (const auto& Element : priorities){
            MaxValue = max(MaxValue, Element);
        }
        
        while (priorities[CurrentFront] != MaxValue){
            CurrentFront = (CurrentFront + 1) % CaseSize;
        }
        
        priorities[CurrentFront] = -1;
        if (location == CurrentFront) return LocationCount;
        
        
        
        LocationCount++;
    }
}

int main ()
{
    vector<int> Vec = {1, 1, 9, 1, 1, 1};
    std::cout << solution(Vec, 0);
    
    return 0;
}