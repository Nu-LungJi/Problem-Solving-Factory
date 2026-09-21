// https://cses.fi/problemset/task/1069/
// Week 1 Day 7
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string Input = ""; 
    std::cin >> Input;
    
    unsigned int RepeatMaxCount = 1, RepeatCount = 1;
    
    for (size_t i = 1; i < Input.size(); ++i) {
        if (Input[i] == Input[i - 1]) RepeatCount++;
        else RepeatCount = 1;
        
        RepeatMaxCount = std::max(RepeatMaxCount, RepeatCount);
    }
    
    std::cout << RepeatMaxCount << " ";
    
    return 0;
}
