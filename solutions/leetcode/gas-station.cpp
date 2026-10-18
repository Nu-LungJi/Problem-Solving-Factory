// https://leetcode.com/problems/gas-station/
// Week 5 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int Size = static_cast<int>(gas.size());
    if (Size == 1) return gas[0] - cost[0] < 0 ? -1 : 0;
    int Result = 0;

    int CurrentGas = 0, TotalGas = 0, TotalCost = 0;
    for (int Start = 0; Start < Size; ++Start) {
        TotalGas += gas[Start];
        TotalCost += cost[Start];
        CurrentGas += (gas[Start] - cost[Start]);

        if (CurrentGas < 0) {
            CurrentGas = 0;
            Result = Start + 1;
        }
    }
        
    return TotalGas >= TotalCost ? Result : -1;
}