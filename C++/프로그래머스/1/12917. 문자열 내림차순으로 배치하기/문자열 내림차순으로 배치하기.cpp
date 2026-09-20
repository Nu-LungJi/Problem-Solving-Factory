#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    
   for (int i = 0; i < s.size(); ++i){
        for (int j = 0; j < s.size(); ++j){
            if (i == j) continue;
            if (s[i] > s[j]) std::swap(s[i], s[j]);
        }
   }

    return s;
}