#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> people, int limit) {
    int Size = static_cast<int>(people.size());
    if (Size == 1) return 1;
    
    std::sort(people.begin(), people.end());
    
    int Front = 0, End = Size - 1, Result = 0;
    while (Front <= End) {
        if (people[Front] + people[End] > limit) {
            End--;
            Result++;
        }
        else {
            Front++; End--;
            Result++;
        }
    }
    return Result;
}