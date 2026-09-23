// https://leetcode.com/problems/implement-queue-using-stacks/
// Week 2 Day 2
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
public:
    MyQueue() = default;
    
    void push(int x) {
        if (!OutputStack.empty()){
            size_t StackSize = OutputStack.size();
            for (size_t i = 0; i < StackSize; ++i) {
                InputStack.push(OutputStack.top());
                OutputStack.pop();
            }
        }
       
        InputStack.push(x);
    }
    
    int pop() {
        // if (OutputStack.empty()) return NULL;

        size_t StackSize = InputStack.size();
        for (size_t i = 0; i < StackSize; ++i){
            OutputStack.push(InputStack.top());
            InputStack.pop();
        }

        int Output = OutputStack.top();
        OutputStack.pop();
        return Output;
    }
    
    int peek() {
        // if (OutputStack.empty()) return NULL;

        size_t StackSize = InputStack.size();
        for (size_t i = 0; i < StackSize; ++i){
            OutputStack.push(InputStack.top());
            InputStack.pop();
        }

        return OutputStack.top();
    }
    
    bool empty() {
        size_t StackSizeA = InputStack.size();
        size_t StackSizeB = OutputStack.size();
        return (StackSizeA + StackSizeB) == 0;
    }

private:
    stack<int> InputStack;
    stack<int> OutputStack;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main()
{
    MyQueue* myQueue = new MyQueue();
    myQueue->push(1); // queue is: [1]
    myQueue->push(2); // queue is: [1, 2] (leftmost is front of the queue)
    std::cout << myQueue->peek() << "\n"; // return 1
    std::cout << myQueue->pop() << "\n"; // return 1, queue is [2]
    std::cout << myQueue->empty() << "\n"; // return false
    
    return 0;
}