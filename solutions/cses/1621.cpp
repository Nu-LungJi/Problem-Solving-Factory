// https://cses.fi/problemset/task/1621/
// Week 1 Day 5
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main_Extra() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int Count = 0;
    std::vector<unsigned int> NumberList;
    
    std::cin >> Count;
    while (Count--) {
        unsigned int Element = 0;
        std::cin >> Element;
        
        NumberList.emplace_back(Element);
    }
    
    std::sort(NumberList.begin(), NumberList.end());
    int unique_count = std::unique(NumberList.begin(), NumberList.end()) - NumberList.begin();
    
    std::cout << unique_count;
    
    return 0;
}

int main() {// another Way
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);    
    std::cout.tie(nullptr);    
    
    std::set<unsigned int> UniqueSet;
    unsigned int Count = 0;
    
    if (!(std::cin >> Count)) return 0;
    
    while (Count--)
    {
        unsigned int Element = 0;
        std::cin >> Element;
        UniqueSet.insert(Element);
    }
    
    std::cout << UniqueSet.size() << " ";
    
    return 0;
}
