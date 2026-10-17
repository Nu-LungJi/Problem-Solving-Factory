// https://leetcode.com/problems/lemonade-change/
// Week 5 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool lemonadeChange(vector<int>& bills) {
    int Size = static_cast<int>(bills.size());

    if (Size == 1) return bills[0] == 5 ? true : false;
    if (bills[0] != 5) return false;

    int CurrentBudget5 = 0, CurrentBudget10 = 0, CurrentBudget20 = 0;
        
    for (const auto& bill : bills) {
        if (bill == 5) {
            CurrentBudget5++;
            continue;
        }
        else if (bill == 10) {
            CurrentBudget10++;
            CurrentBudget5--;
        }
        else {
            CurrentBudget20++;
            if (CurrentBudget10 > 0) {
                CurrentBudget10--;
                CurrentBudget5--;
            }
            else {
                CurrentBudget5 -= 3;
            }
        }
        if (CurrentBudget5 < 0 || CurrentBudget10 < 0 || CurrentBudget20 < 0) return false;
    }
    return true;
}