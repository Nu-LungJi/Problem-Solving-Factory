#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
    int Size = static_cast<int>(times.size());
    long long MaxPerson = static_cast<long long>(n);
    
    long long Front = 1;
    long long End = *std::max_element(times.begin(), times.end()) * MaxPerson;
    long long Result = 0;
    
    if (Size == 1) return End;
    
    while (Front <= End) {
        long long Middle = (Front + End) / 2;
        long long Person = 0;
        for (const auto& Element : times)  {
            Person += Middle / static_cast<long long>(Element);
            if (Person > MaxPerson) break;
        }
        
        if (MaxPerson <= Person) {
            Result = Middle;
            End = Middle - 1;
        }
        else {
            Front = Middle + 1;
        }
    }
    
    return Result;
    
}