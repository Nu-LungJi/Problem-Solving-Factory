// https://school.programmers.co.kr/learn/courses/30/lessons/12909
// Week 2 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <iostream>

using namespace std;

bool solution(string s) {
    int OpenCount = 0;
    for (const auto& Element : s){
        if (Element == '('){
            OpenCount++;
        }
        else {
            if (OpenCount == 0) return false;
            OpenCount--;
        }
    }
    
    if (OpenCount != 0) return false;
    
    return true;
}

int main()
{
    std::cout << boolalpha;
    std::cout << solution("(())()");
    
    return 0;
}