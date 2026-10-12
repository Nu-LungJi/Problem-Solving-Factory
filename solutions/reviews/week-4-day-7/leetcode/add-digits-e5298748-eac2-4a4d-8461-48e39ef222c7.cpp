// https://leetcode.com/problems/add-digits/
// Week 4 Day 7
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int addDigits(int num) {
    while (num >= 10) {
        string X = std::to_string(num);
        int Sum = 0;
        for (const auto& Element : X) {
            Sum += Element - '0';
        }
        num = Sum;
    }
    
    return num;
}

int addDigits2(int num) {
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