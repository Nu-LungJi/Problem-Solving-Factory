// https://leetcode.com/problems/number-of-recent-calls/
// Week 2 Day 3
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

class RecentCounter {
public:
    RecentCounter() {
        
    }
    
    int ping(int t) {
        PingQueue.emplace_back(t);
        while (PingQueue.front() < t - 3000) {
            PingQueue.pop_front();
        }

        return static_cast<int>(PingQueue.size());
    }

private:
    std::deque<int> PingQueue;
};

int main()
{
    RecentCounter R;
    std::cout << R.ping(1) << " ";
    std::cout << R.ping(100) << " ";
    std::cout << R.ping(3001) << " ";
    std::cout << R.ping(3002) << " ";
    
    return 0;
}