// https://leetcode.com/problems/design-circular-queue/
// Week 2 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        Queue.resize(k, -1);
        Forward = Queue.size() - 1;
        Backward = 0;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        Queue[Backward++] = value;
        if (Backward == Queue.size()) Backward = 0;

        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        if (Forward == Queue.size() - 1) Forward = -1;
        Queue[++Forward] = -1;

        return true;
    }
    
    int Front() {
        int Index = Forward + 1;
        if (Index > Queue.size() - 1) Index = 0;
        return Queue[Index];
    }
    
    int Rear() {
        int Index = Backward - 1;
        if (Index < 0) Index = Queue.size() - 1;
        return Queue[Index];
    }
    
    bool isEmpty() {
        for (size_t i = 0; i < Queue.size(); ++i){
            if (Queue[i] != -1) return false;
        }
        return true;
    }
    
    bool isFull() {
        for (size_t i = 0; i < Queue.size(); ++i){
            if (Queue[i] == -1) return false;
        }
        return true;
    }

private:
    vector<int> Queue;
    int Forward, Backward;
};