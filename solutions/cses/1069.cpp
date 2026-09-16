// https://cses.fi/problemset/task/1069/
// Week 1 Day 2
#include <iostream>
using namespace std;

int main() {
    int MaxLength = 1, LengthCount = 1;
    string DNA;
    cin >> DNA;
    
    for (size_t i = 1; i < DNA.size(); ++i) {
        if (DNA[i] == DNA[i - 1]) {
            LengthCount++;
            MaxLength = max<int>(MaxLength, LengthCount);
            continue;
        }
        LengthCount = 1;
    }
    
    std::cout << MaxLength << "\n";
    return 0;
}
