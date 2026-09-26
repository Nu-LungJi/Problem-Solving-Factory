// https://school.programmers.co.kr/learn/courses/30/lessons/42576
// Week 2 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;


#include <string>
#include <vector>
#include <set>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    std::multiset<string> Container;
    for (const auto& Element : participant){
        Container.emplace(Element);
    }
    
    for (const auto& Element : completion){
        auto iter = Container.find(Element);
        if (iter != Container.end()){
            Container.erase(iter);
        }
    }
    string Result = "";
    for (const auto& Element : Container){
        Result = Element;
    }
    return Result;
}


int main()
{
    std::cout << solution(vector<string>{"mislav", "stanko", "mislav", "ana"}, 
        vector<string>{"stanko", "ana", "mislav"});
    return 0;
}