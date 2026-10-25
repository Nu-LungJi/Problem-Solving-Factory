// https://leetcode.com/problems/jump-game-iii/
// Week 6 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int Size;
    bool Flag = false;
    vector<bool> Visited;
    void DFS(vector<int>& arr, int start) {
        if (Flag || arr[start] == 0) {
            Flag = true;
            return;
        }

        if (!Flag && start + arr[start] < Size&& !Visited[start + arr[start]]) {
            Visited[start + arr[start]] = true;
            DFS(arr, start + arr[start]);
            Visited[start + arr[start]] = false;
        }
        if (!Flag && start - arr[start] >= 0 && !Visited[start - arr[start]]) {
            Visited[start - arr[start]] = true;
            DFS(arr, start - arr[start]);
            Visited[start - arr[start]] = false;
        }
    }
    bool canReach(vector<int>& arr, int start) {
        Size = static_cast<int>(arr.size());
        Visited.resize(Size, false);
        DFS(arr, start);

        return Flag;
    }
};