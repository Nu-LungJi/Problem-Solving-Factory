// https://school.programmers.co.kr/learn/courses/30/lessons/42578
// Week 2 Day 6
// Paste the platform function signature, then implement your solution.
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    unordered_map<string, int> MM;
    for (const auto& Elem : clothes) {
        if (MM.count(Elem[1]) >= 1){
            MM[Elem[1]] += 1;
        }
        else{
            MM[Elem[1]] = 1;
        }
    }
    
    int Result = 1;
    for (auto iter = MM.begin(); iter != MM.end();) {
        Result = Result * (iter->second + 1);
        ++iter;
    }
    Result -= 1;
    
    return Result;
}

int main() {
    vector<vector<string>> Input = {{"yellow_hat", "headgear"}, {"blue_sunglasses", "eyewear"}
        , {"green_turban", "headgear"}};
    
    std::cout << solution(Input);
    return 0;
}