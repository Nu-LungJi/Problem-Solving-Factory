// https://leetcode.com/problems/possible-bipartition/
// Week 6 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    std::vector<std::vector<int>> Graph;
    bool BFS(std::vector<int>& List, int Size) {
        queue<int> Queue;
        Queue.push(1);

        for (int i = 1; i <= Size; ++i) {
            if (List[i] != 0) continue;
            Queue.push(i);

            while (!Queue.empty()) {
                int Top = Queue.front();
                Queue.pop();

                for (int Next : Graph[Top]) {
                    if (List[Next] == 0) {
                        List[Next] = (List[Top] == 1) ? 2 : 1;
                        Queue.push(Next);
                    }
                    else if (List[Next] == List[Top]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        Graph.resize(n + 1);
        for (const auto& Elem : dislikes) {
            Graph[Elem[0]].push_back(Elem[1]);
            Graph[Elem[1]].push_back(Elem[0]);
        }

        std::vector<int> TeamList(n + 1, 0);

        if (!BFS(TeamList, n)) return false;

        return true;
    }
};