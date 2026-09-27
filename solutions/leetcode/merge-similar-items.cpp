// https://leetcode.com/problems/merge-similar-items/
// Week 2 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
    unordered_map<int, int> UM1, UM2;

    for (const auto& Element : items1) {
        UM1.insert({Element[0], Element[1]});
    }

    for (const auto& Element : items2) {
        UM2.insert({Element[0], Element[1]});
    }

    for (const auto& Element : UM2){
        auto iter = UM1.find(Element.first);
        if (iter == UM1.end()) UM1.insert(Element);
        else {
            iter->second += Element.second;
        }
    }

    vector<vector<int>> Result;
    for (const auto& Element : UM1){
        Result.emplace_back(vector<int>{Element.first, Element.second});
    }
    std::sort(Result.begin(), Result.end());

    return Result;
}

int main()
{
    vector<vector<int>> InputA = {{1,1},{4,5},{3, 8}};
    vector<vector<int>> InputB = {{3,1},{1,5}};
    
    auto Result = mergeSimilarItems(InputA, InputB);
    
    for (const auto& i : Result)
    {
        std::cout << "[ " << i[0] << " " << i[1] << " ]" << ", ";
    }
    return 0;
}