// https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/
// Week 2 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int countStudents(vector<int>& students, vector<int>& sandwiches) {
    int CurrentSandwitchIndex = 0, CurrentStudentIndex = 0;
    int NotEatStudent = static_cast<int>(students.size());

    while(true) {
        for (size_t i = CurrentStudentIndex; i < students.size(); ++i){
            if (students[i] == -1) continue;

            if (sandwiches[CurrentSandwitchIndex] == students[i]){
                std::swap(students[i], students[CurrentStudentIndex++]);
                    
                if (--NotEatStudent == 0) return 0;

                ++CurrentSandwitchIndex;
                break;
            }

            if (i == students.size() - 1) return NotEatStudent;
        }
    }
        
    return NotEatStudent;
}

int main() {
    vector<int> A = {1,1,1,0,0,1};
    vector<int> B = {1,0,0,0,1,1};
    
    std::cout << countStudents(A, B);
    return 0;
}