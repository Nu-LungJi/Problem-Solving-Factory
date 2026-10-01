// https://cses.fi/problemset/task/1622/
// Week 3 Day 3
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
   
    std::string Input = "";
    std::cin >> Input;
    
    std::vector<std::string> OutputVec;
    int Count = 0;
    
    std::sort(Input.begin(), Input.end());
    
    do {
        OutputVec.emplace_back(Input);
        Count++;
    }while (std::next_permutation(Input.begin(), Input.end()));
    
    std::cout << Count << "\n";
    for (const auto& Element : OutputVec) std::cout << Element << "\n";
    
    return 0;
}