// https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/
// Week 5 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int minMovesToSeat(vector<int>& seats, vector<int>& students) {
    int StuSize = static_cast<int>(students.size());
    if (StuSize == 1) return std::abs(students[0] - seats[0]);

    std::sort(seats.begin(), seats.end());
    std::sort(students.begin(), students.end());

    int Front = 0, Result = 0;

    for (int i = 0; i < StuSize; ++i) {
        Result += std::abs(students[i] - seats[i]);
    }

    return Result;
}