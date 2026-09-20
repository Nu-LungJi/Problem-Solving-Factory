// https://school.programmers.co.kr/learn/courses/30/lessons/12901
// Week 1 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

string solution(int a, int b) {
    std::array<int, 12> MonthArray{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    std::array<string, 7> WeekDayArray = {"FRI","SAT","SUN","MON","TUE","WED", "THU"};
    
    
    int Result = 0;
    
    for (int i = 0; i < a - 1; ++i){
        Result += MonthArray[i];
    }
    Result += (b - 1);
    
    return WeekDayArray[(Result % 7)];
    
    
    string answer = "";
    return answer;
}

int main()
{
    std::cout << solution(2, 29).c_str();
    return 0;
}