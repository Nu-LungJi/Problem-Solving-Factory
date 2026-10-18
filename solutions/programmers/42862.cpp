// https://school.programmers.co.kr/learn/courses/30/lessons/42862
// Week 5 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int LostSize = static_cast<int>(lost.size());
    int ReserveSize = static_cast<int>(reserve.size());
    
    std::sort (lost.begin(), lost.end());
    std::sort (reserve.begin(), reserve.end());
    
    int a = 0, b = 0, Result = n - LostSize;
    while (a != LostSize && b != ReserveSize) {
        if (lost[a] < reserve[b]) {
            a++;
        }
        else if (lost[a] > reserve[b]) {
            b++;
        }
        else {
            lost[a] = 0; reserve[b] = 0;
            a++;b++;
            Result++;
        }
    }

    int LostFront = 0, ReserveFront = 0;
    while (Result != n && ReserveFront != ReserveSize &&
          LostFront != LostSize) {
        if (lost[LostFront] == 0) {LostFront++; continue;}
        if (reserve[ReserveFront] == 0) {ReserveFront++; continue;}
        
        if (lost[LostFront] - 1 == reserve[ReserveFront] ||
            lost[LostFront] + 1 == reserve[ReserveFront]) {
            LostFront++; ReserveFront++;
            Result++;
            }
        else if (lost[LostFront] + 1 < reserve[ReserveFront]) {
            LostFront++;
        }
        else {
            ReserveFront++;
        }
          }
    return Result;
}