#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> PQ;
    
    for (const auto& Element : scoville) {
        PQ.emplace(Element);
    }
    
    int Count = 0;
    
    while (PQ.top() < K && PQ.size() > 1){
        int X = PQ.top(); PQ.pop();
        int Y = PQ.top(); PQ.pop();
        
        PQ.emplace(X + (Y * 2));
        Count++;
    }
    
    if (PQ.top() < K && PQ.size() <= 1) return -1;

    return Count;
}