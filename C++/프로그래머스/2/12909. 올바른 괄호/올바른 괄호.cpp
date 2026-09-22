#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool solution(string s) {
    int OpenCount = 0;
    for (const auto& Element : s){
        if (Element == '('){
            OpenCount++;
        }
        else {
            if (OpenCount == 0) return false;
            OpenCount--;
        }
    }
    
    if (OpenCount != 0) return false;
    
    return true;
}