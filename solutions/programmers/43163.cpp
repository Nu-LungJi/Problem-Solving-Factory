// https://school.programmers.co.kr/learn/courses/30/lessons/43163
// Week 6 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <vector>
#include <queue>
using namespace std;

int Size, Case;

bool CompareOnlyOne(const string& A, const string& B) {
    int Count = 0;
    for (int i = 0; i < Size; ++i) {
        if (A[i] != B[i]) Count++;
        if (Count >= 2) return false;
    }
    return Count == 1 ? true : false;
}

int BFS(string& begin, const string& target, vector<string>& words) {
    vector<bool> Visit(Case, false);
    queue<string> Queue;
    Queue.push(begin);
    
    int Ret = 0;
    while (!Queue.empty()) {
        int Count = static_cast<int>(Queue.size());
        for (int k = 0; k < Count; ++k){
            auto Top = Queue.front();
            Queue.pop();
            if (Top == target) return Ret;
            
            for (int i = 0; i < Case; ++i) {
                if (!Visit[i] && CompareOnlyOne(words[i], Top)) {
                    Visit[i] = true;
                    Queue.push(words[i]);
                }
            }
        }
        Ret++;
    }
    return Ret;
}


int solution(string begin, string target, vector<string> words) {
    Size = static_cast<int>(begin.size());
    Case = static_cast<int>(words.size());
    
    auto iter = words.begin();
    for (;iter != words.end(); ++iter) {
        if (*iter == target) break;
    }
    if (iter == words.end()) return 0;
    
    return BFS(begin, target, words);
}