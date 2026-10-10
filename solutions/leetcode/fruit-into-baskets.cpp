// https://leetcode.com/problems/fruit-into-baskets/
// Week 4 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int Size = static_cast<int>(fruits.size());
        vector<int> FruitVar(Size, 0);

        if (Size == 1) return 1;

        int CurFront = 0, CurBack = 1, MaxTree = 0, Var = 1;
        FruitVar[fruits[0]]++;
        while (CurBack < Size) {
            while (Var > 2){
                int Index = fruits[CurFront++];
                if (--FruitVar[Index] == 0) Var--;
            }
            if (++FruitVar[fruits[CurBack++]] == 1) Var++;

            if (Var <= 2) MaxTree = std::max(MaxTree, CurBack - CurFront);
        }

        return MaxTree;
    }
};