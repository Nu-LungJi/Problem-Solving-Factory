// https://leetcode.com/problems/intersection-of-two-arrays/
// Week 1 Day 5
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());

        auto UniqueiterEnd1 = std::unique(nums1.begin(), nums1.end());
        auto UniqueiterEnd2 = std::unique(nums2.begin(), nums2.end());

        vector<int> ResultVec, CompareVec;
        CompareVec.insert(CompareVec.end(), nums1.begin(), UniqueiterEnd1);
        CompareVec.insert(CompareVec.end(), nums2.begin(), UniqueiterEnd2);

        unordered_set<int> UniqueSet;
        vector<int> v;

        for (const auto& Element : CompareVec){

            if (UniqueSet.count(Element)){
                ResultVec.emplace_back(Element);
            }
            else {
                UniqueSet.insert(Element);
            }
        }

        return ResultVec;
    }
};


int main() {
    Solution S;
    
    std::cout << boolalpha;
    
    vector<int> NumbersA = {1, 2, 3, 1};
    vector<int> NumbersB = {1, 2, 3, 4};

	auto Result = S.intersection(NumbersA, NumbersB);

	for (const auto& Element : Result){
    	std::cout << Element << "\n";
	}

    return 0;
}