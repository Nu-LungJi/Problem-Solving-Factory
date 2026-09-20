#include <string>
#include <vector>
#include <array>

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