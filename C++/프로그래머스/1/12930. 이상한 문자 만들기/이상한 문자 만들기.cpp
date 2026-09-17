#include <string>
#include <vector>

using namespace std;

const int CaseDiff = 32;
const int ASCII_BLANK = 32;

string solution(string s) {
    int Index = 0;
    for (int i = 0; i < s.size(); ++i){
        if (s[i] == ASCII_BLANK) { 
            Index = 0; 
            continue;
        }
        
        if (Index % 2 == 0) { 
            if (s[i] >= 97) s[i] -= CaseDiff;
        }
        else {
            if (s[i] <= 90) s[i] += CaseDiff;
        }
        Index++;
    }
    
    return s;
}