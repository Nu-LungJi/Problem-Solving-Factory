#include <string>
#include <vector>

using namespace std;

int solution(vector<int> priorities, int location) {
    int CurrentFront = 0;
    int CaseSize = priorities.size();
    
    int LocationCount = 1;
    
    while(true){
        int PRValue = priorities[CurrentFront];
        for (size_t i = 0; i < CaseSize; ++i){
            if (priorities[i] == -1 || CurrentFront == i) continue;
            if (PRValue < priorities[i]){
                PRValue = priorities[i];
                CurrentFront = i;
            }
        }
        
        if (location == CurrentFront) return LocationCount;
        
        priorities[CurrentFront] = -1;
        
        CurrentFront = (CurrentFront + 1) % CaseSize;
        while (true){
            if (priorities[CurrentFront] != -1) break;
            CurrentFront = (CurrentFront + 1) % CaseSize;
        }


        LocationCount++;
    }
    
    
    
    
    int answer = 0;
    return answer;
}