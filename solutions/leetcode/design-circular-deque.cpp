// https://leetcode.com/problems/design-circular-deque/
// Week 2 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class MyCircularDeque {
public:
    MyCircularDeque(int k) {
        CircularQueue.resize(k, -1);
        Rear = 0;
        Front = CircularQueue.size() - 1;
    }

    bool insertFront(int value) {
        if (isFull()) return false;
        if (Front < 0) Front = CircularQueue.size() - 1;
        CircularQueue[Front--] = value;

        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        if (Rear > CircularQueue.size() - 1) Rear = 0;
        CircularQueue[Rear++] = value;

        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;

        int Value = Front + 1;
        if (Value > CircularQueue.size() - 1) Value = 0;
        CircularQueue[Value] = -1;
        Front = Value;

        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;

        int Value = Rear - 1;
        if (Value < 0) Value = CircularQueue.size() - 1;
        CircularQueue[Value] = -1;
        Rear = Value;

        return true;
    }
    
    int getFront() {
        int Value = Front + 1;

         if (Value > CircularQueue.size() - 1) Value = 0;
        return CircularQueue[Value];
    }
    
    int getRear() {
        int Value = Rear - 1;

        if (Value < 0) Value = CircularQueue.size() - 1;
        return CircularQueue[Value];
    }
    
    bool isEmpty() {
        for (size_t i = 0; i < CircularQueue.size(); ++i){
            if (CircularQueue[i] != -1) return false;
        }
        return true;
    }
    
    bool isFull() {
        for (size_t i = 0; i < CircularQueue.size(); ++i){
            if (CircularQueue[i] == -1) return false;
        }
        return true;
    }
private:
    vector<int> CircularQueue;
    int Front, Rear;
};

int main() {
    MyCircularDeque* obj = new MyCircularDeque(3);
    std::cout << obj->insertLast(1) << "\n";
    std::cout << obj->insertLast(2) << "\n";
    std::cout << obj->insertFront(3) << "\n";
    std::cout << obj->insertFront(4) << "\n";
    std::cout << obj->getRear() << "\n";
    std::cout << obj->isFull() << "\n";
    std::cout << obj->deleteLast() << "\n";
    std::cout << obj->insertFront(4) << "\n";
    std::cout << obj->getFront() << "\n";

    return 0;
}