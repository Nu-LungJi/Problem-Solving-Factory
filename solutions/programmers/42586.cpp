// https://school.programmers.co.kr/learn/courses/30/lessons/42586
// Week 2 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    size_t CurrentCount = 0;
    vector<int> answer;
    
    while(true){
        int PublishCount = 0;
        
        int a = 100 - progresses[CurrentCount];
        int b = speeds[CurrentCount];
        
        int aa = a / b;
        int bb = a % b;
        
        if (bb > 0) aa++;
        
        for (size_t i = CurrentCount; i < progresses.size(); i++){
            progresses[i] += speeds[i] * aa;
        }
        
        for (size_t i = CurrentCount; i < progresses.size(); i++){
            if (progresses[i] >= 100) {
                CurrentCount++;
                PublishCount++;
            }
            else {
                CurrentCount = i;
                break;
            }
        }
        if (PublishCount != 0) answer.emplace_back(PublishCount);
        
        if (CurrentCount >= progresses.size()) break;
    }
    
    

    return answer;
}

int main()
{
    vector<int> InputPrg = {95, 90, 99, 99, 80, 99};
    vector<int> InputSpd = {1, 1, 1, 1, 1, 1};
    const auto& Alpha = solution(InputPrg, InputSpd); 

    for (const auto& Elem : Alpha)
    {
        std::cout << Elem << " ";
    }
    return 0;
}