// https://leetcode.com/problems/add-digits/
// Week 1 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int addDigits(int num) {
        int result = 0;
        while(true){
            uint32_t Sum = 0;
            uint32_t Factor = 1;
            for (uint32_t i = 1; i < 32; ++i){
                int First = num / Factor;
                if (First == 0) break;

                int Second = num / (Factor * 10) * 10;
                Sum += First - Second;
                Factor *= 10;
            }
            
            if (Sum < 10) {
                result = Sum;
                break;
            }
            num = Sum;
        }
       
        return result;
    }
};

int main()
{
    Solution Quest;
    cout << "Result 1 : " << Quest.addDigits(38)            << "\n";
    cout << "Result 2 : " << Quest.addDigits(123253453)     << "\n";
    cout << "Result 3 : " << Quest.addDigits(0)             << "\n";
    cout << "Result 4 : " << Quest.addDigits(5433453)       << "\n";
    cout << "Result 5 : " << Quest.addDigits(677899)        << "\n";
    cout << "Result 6 : " << Quest.addDigits(2032610959)    << "\n";
    
    return 0;
}