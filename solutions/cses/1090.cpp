// https://cses.fi/problemset/task/1090/
// Week 5 Day 5
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ChildrenCount = 0, MaxChildrenWeight = 0;
    std::cin >> ChildrenCount >> MaxChildrenWeight;
    
    std::vector<int> ChildrenWeight(ChildrenCount);
    for (int i = 0; i < ChildrenCount; i++) std::cin >> ChildrenWeight[i]; 
    
    int GondolaCount = 0;
    std::sort(ChildrenWeight.begin(), ChildrenWeight.end());
    
    int Front = 0, Back = ChildrenCount - 1;

    while (Front <= Back) {
        if (Front == Back) {
            GondolaCount++;
            break;
        }
        if (ChildrenWeight[Back] + ChildrenWeight[Front] > MaxChildrenWeight) {
            Back--;
            GondolaCount++;
        }
        else {
            Back--;
            Front++;
            GondolaCount++;
        }
    }
    
    std::cout << GondolaCount << "\n";
    return 0;
}
