// https://leetcode.com/problems/keys-and-rooms/
// Week 6 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

stack<int> RoomRoute;
vector<uint8_t> HasKey;

void Recur(vector<vector<int>>& rooms) {
    int top = RoomRoute.top();
    RoomRoute.pop();

    HasKey[top] = true;

    for (int j = 0; j < rooms[top].size(); ++j) {
        if (!HasKey[rooms[top][j]]) RoomRoute.push(rooms[top][j]);
        //HasKey[rooms[top][j]] = true;
    }

    if (!RoomRoute.empty()) Recur(rooms);
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int RoomCount = static_cast<int>(rooms.size());
    if (RoomCount == 1)         return true;
    if (rooms[0].size() == 0)   return false;

    HasKey.resize(RoomCount, false);
    HasKey[0] = true;

    for (int j = 0; j < static_cast<int>(rooms[0].size()); ++j) {
        RoomRoute.push(rooms[0][j]);
        //HasKey[rooms[0][j]] = true;
    }

    Recur(rooms);

    for (const auto& Elem : HasKey) {
        if (Elem == false) return false;
    }

    return true;
}