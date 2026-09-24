#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    //auto iter = std::unique(arr.begin(), arr.end());
    //arr.erase(iter, arr.end());

    //return arr;
    vector<int> Answer;
    for (size_t i = 1; i < arr.size(); ++i){
        if (arr[i - 1] == arr[i]){
            while (i < arr.size() - 1 && arr[i - 1] == arr[i]) { ++i; }
        }
        
        Answer.emplace_back(arr[i - 1]);
        
        if (i == arr.size() - 1 && arr[i - 1] != arr[i]) 
            Answer.emplace_back(arr[i]);
    }
    
    return Answer;
}