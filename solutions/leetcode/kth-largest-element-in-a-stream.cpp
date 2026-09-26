// https://leetcode.com/problems/kth-largest-element-in-a-stream/
// Week 2 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : kth(k) {
        std::sort(nums.begin(), nums.end());
        if (nums.size() < kth){
            for (const auto& Element : nums){
                PQ.emplace(Element);
            }
        }
        else if (nums.size() > 0) {
            for (auto iter = nums.end() - k; iter != nums.end(); ++iter){
                PQ.emplace(*iter);
            }
        }
    }
    
    int add(int val) {
        if (PQ.size() < kth) {
            PQ.emplace(val);
            return PQ.top();
        }

        if (PQ.top() < val){
            PQ.pop();
            PQ.emplace(val);
        } 
        return PQ.top();
    }
    
    void ClearAndPrint ()
    {
        size_t Size = PQ.size();
        for (size_t i = 0; i< Size; ++i) {
            std::cout << PQ.top() << " ";
            PQ.pop();
        }
    }
private:
    priority_queue<int, vector<int>, greater<int>> PQ;
    int kth;
};

int main ()
{
    auto Input = vector<int>{4,5,8,2};
    KthLargest K(3, Input);
    K.add(3);
    K.add(5);
    K.add(10);
    K.add(9);
    K.add(4);
    
    K.ClearAndPrint();
    
    return 0;
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */