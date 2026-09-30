// https://leetcode.com/problems/powx-n/
// Week 3 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

double Result = 1.00000;

double myPow(double x, int n) {
    if (x == -1.00) return n % 2 == 0 ? 1.00 : -1.00;
    if (x ==  1.00) return 1.00;

    long long Factor = n;
    Factor = n < 0 ? -Factor : Factor;

    while (Factor > 0){

        if (Factor % 2 == 1) {
            Result *= x;
            Factor -= 1;
        }
        else {
            x = x*x;
            Factor /= 2;
        }
    }

    return n < 0 ? 1.00 / Result : Result;
}