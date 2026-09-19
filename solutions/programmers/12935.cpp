// https://school.programmers.co.kr/learn/courses/30/lessons/12935
// Week 1 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer = arr;
    if (arr.size() <= 1) return vector<int>(1, -1);
    sort(arr.begin(), arr.end());

    for (auto iter = answer.begin(); iter != answer.end();){
        if ((*iter) == arr[0]) {
            answer.erase(iter);
            break;
        }
        iter++;
    }
    return answer;
}

int main()
{
    vector<int> Input = { 4, 3, 2, 1 };
    auto Output = solution(Input);
    
    for (const auto& Element : Output)
    {
        std::cout << Element << " ";
    }
    return 0;
}