#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int Result = 1;
    int Minimum = 0;
    int PastSum = 1;
    for (int i = 2; i <= n; ++i) {
        int FrontNumb = 1, BackNumb = i, Sum = 0;
        PastSum = Sum = PastSum + BackNumb;
        
        if (Sum > n) break;
        
        while (BackNumb != n) {
            if (Sum == n) {
                Result++;
                break;
            }
            else if (Sum > n) break;
            else {
                Sum -= FrontNumb++;
                Sum += ++BackNumb;
            }
        }
    }
    
    return Result;
    
}