// https://cses.fi/problemset/task/1640/
// Week 4 Day 3
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ArraySize = 0, Target = 0;
    std::cin >> ArraySize >> Target;
    
    std::vector<int> Array; 
    int FrontPTR = 0, BackPTR = ArraySize - 1, Size = ArraySize;
    int Element = 0;
    while (ArraySize-- && std::cin >> Element) {
        Array.push_back(Element);
    }
    std::vector<int> OriginArray = Array;
    std::sort(Array.begin(), Array.end());
    
    while (FrontPTR < BackPTR) {
        if (Target < Array[FrontPTR] + Array[BackPTR]) {
            BackPTR--;
        }
        else if (Target > Array[FrontPTR] + Array[BackPTR]) {
            FrontPTR++;
        }
        else {
            bool Front = true, Back = true;
            for (int i = 0; i < Size; ++i) {
                if (Front && Array[FrontPTR] == OriginArray[i]) {
                    std::cout << i + 1 << " ";
                    Front = false;
                }
                if (Back && Array[BackPTR] == OriginArray[Size - 1 - i]) {
                    std::cout << Size - i << " ";
                    Back = false;
                }
                if (!Front && !Back) return 0;
            }
        }
    }
    std::cout << "IMPOSSIBLE";
    
    return 0;
}
