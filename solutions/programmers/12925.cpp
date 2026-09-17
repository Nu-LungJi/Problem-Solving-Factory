// https://school.programmers.co.kr/learn/courses/30/lessons/12925
// Week 1 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int ASCII_0 = 48;
const int ASCII_MINUS = 45;

int solution(string s) {
    int answer = 0;
    if (s[0] == ASCII_0)        return answer;
    
    int StringSize = s.size();

    for (int i = 0; i < StringSize; ++i){
        if (s[i] < ASCII_0) continue;
        int Numb = s[i] - ASCII_0;
        
        int LoopCount = StringSize - i - 1;
        while(LoopCount--) { Numb *= 10; }
        
        answer += Numb;
    }
    
    if (s[0] == ASCII_MINUS)    return -answer;
    
    return answer;
}

int main() {
    std::cout << solution("   fly me   to   the moon  ");
    return 0;
}