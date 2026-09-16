// https://cses.fi/problemset/task/1094/
// Week 1 Day 2
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    unsigned long DiffSum = 0;
    unsigned int ArraySize = 0;
    cin >> ArraySize;
    
    long PrevElement = 0, CurrentElement = 0;
    for (unsigned int i = 0; i < ArraySize; ++i) {
        cin >> CurrentElement;
        long Diff = PrevElement - CurrentElement;
        if (Diff > 0) {
            DiffSum += Diff;
            CurrentElement += Diff;
        }
        PrevElement = CurrentElement;
    }
    
    cout << DiffSum << "\n";
    
    return 0;
}
