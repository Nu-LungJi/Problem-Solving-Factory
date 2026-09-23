// https://leetcode.com/problems/time-needed-to-buy-tickets/
// Week 2 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


int timeRequiredToBuy(vector<int>& tickets, int k) {
    int TotalSecond = 0;
    int CurrentFront = k;

    while(true){
        for (auto& Element : tickets){
            if (Element > 0){
                Element -= 1;
                TotalSecond += 1; 
                if (tickets[k] == 0) return TotalSecond;
            } // 40 + 21 + 6 * 15 = 151
        }
        if (tickets[k] == 0) break;
    }
    return TotalSecond;
}


int main ()
{
    vector<int> Vec = {2,3,2};
    std::cout << timeRequiredToBuy(Vec, 2);
    return 0;
}