// https://leetcode.com/problems/fibonacci-number/
// Week 3 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int Process(int n){
    if (n <= 1) return n;
    return Process(n - 1) + Process(n - 2);
}
int fib(int n) {
    return Process(n);
}

int fib2(int n) {
    if (n <= 1) return n;
    int Prev01 = 0, Prev02 = 1;
    int Result = Prev01 + Prev02;
    for (int i = 2; i <= n; ++i) {
        Result = Prev01 + Prev02;
        Prev01 = Prev02;
        Prev02 = Result;
    }

    return Result;
}

int fib3(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}