// https://leetcode.com/problems/range-sum-query-immutable/
// Week 4 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class NumArray {
private:
    vector<int> Query;
public:
    NumArray(vector<int>& nums) {
        int Size = static_cast<int>(nums.size());
        Query.push_back(nums[0]);
        for (int i = 1; i < Size; ++i){
            Query.push_back(Query[i - 1] + nums[i]);
        }
    }
    
    int sumRange(int left, int right) {
        if (left == 0) return Query[right];
        return Query[right] - Query[left - 1];
    }

};