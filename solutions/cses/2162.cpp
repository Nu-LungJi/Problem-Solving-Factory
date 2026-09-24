// https://cses.fi/problemset/task/2162/
// Week 2 Day 3
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int ChildrenCount = 0, CurrentIndex = -1, DeletedCount = 0;
    std::cin >> ChildrenCount;
    
    std::vector<int> Children(ChildrenCount, 1);
    
    if (ChildrenCount <= 0) return 0;
    
    while (DeletedCount != ChildrenCount) {
        while (true) {
            CurrentIndex = (CurrentIndex + 1) % ChildrenCount;
            if (Children[CurrentIndex] != -1)
            {
                while (true)
                {
                    CurrentIndex = (CurrentIndex + 1) % ChildrenCount;
                    if (Children[CurrentIndex] != -1) break;
                }
                break;
            }
        }
        Children[CurrentIndex] = -1;
        DeletedCount++;
        std::cout << CurrentIndex + 1 << " ";
    }
    
    std::vector<int> A;
    A.resize(3, -1);
    for (const auto& i : A)
    {
        std::cout << i << " ";
    }
    return 0;
}