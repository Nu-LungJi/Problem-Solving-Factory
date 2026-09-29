// https://school.programmers.co.kr/learn/courses/30/lessons/42840
// Week 3 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
using namespace std;

constexpr int ReA = 5;
constexpr int ReB = 8;
constexpr int ReC = 10;

const array<int, ReA> arrA = { 1, 2, 3, 4, 5 };
const array<int, ReB> arrB = { 2, 1, 2, 3, 2, 4, 2, 5 };
const array<int, ReC> arrC = { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 }; 

vector<int> solution(vector<int> answers) {
    int A = 0, B = 0, C = 0;
    int Size = static_cast<int>(answers.size());
    
    for (int i = 0; i < Size; ++i) {
        int Answer = answers[i];
        if (arrA[i % ReA] == Answer) A++;
        if (arrB[i % ReB] == Answer) B++;
        if (arrC[i % ReC] == Answer) C++;
    }
    
    int Max = std::max(std::max(A, B), C);
    
    vector<int> Result;
    if (Max == A) Result.emplace_back(1);
    if (Max == B) Result.emplace_back(2);
    if (Max == C) Result.emplace_back(3);
                         
    return Result;
}

int main() {
    vector<int> Input = { 1,3,2,4,2 };
    auto Result = solution(Input);
    
    for (const auto& Element : Result) {
        std::cout << Element << " ";
    }
    return 0;
}