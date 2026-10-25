// https://school.programmers.co.kr/learn/courses/30/lessons/43165
// Week 6 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <vector>

using namespace std;
int Size, Result = 0;
void DFS(vector<int>& numbers, int& target, int& Sum, int Start) {
    if (Sum == target) {
        Result++;
        return;
    }
    
    for (int i = Start; i < numbers.size(); ++i) {
        if (Sum - numbers[i] * 2 >= target){
            Sum -= numbers[i] * 2;
            DFS(numbers, target, Sum, i + 1);
            Sum += numbers[i] * 2;
        }
    }
}

int solution(vector<int> numbers, int target) {
    Size = static_cast<int>(numbers.size());
    
    int Sum = 0;
    for (const auto& Elem : numbers) Sum += Elem;
    DFS(numbers, target, Sum, 0);
    return Result;
}