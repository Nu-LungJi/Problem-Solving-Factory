// https://school.programmers.co.kr/learn/courses/30/lessons/12917
// Week 1 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string solution(string s) {
    
    for (int i = 0; i < s.size(); ++i){
        for (int j = 0; j < s.size(); ++j){
            if (i == j) continue;
            if (s[i] > s[j]) std::swap(s[i], s[j]);
        }
    }

    return s;
}

int main()
{
    std::cout << solution("isphdfiubasASFSFDGweubrfi").c_str();
    return 0;
}