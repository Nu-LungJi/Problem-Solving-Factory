// https://leetcode.com/problems/snakes-and-ladders/
// Week 6 Day 4
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int BFS(vector<vector<int>>& board) {
    int Size = static_cast<int>(board.size());
    int End = Size * Size;

    queue<int> Queue;
    vector<bool> Visited(End + 1, false);

    Queue.push(1);
    Visited[1] = true;

    int Step = 0;

    while (!Queue.empty()) {
        int Count = static_cast<int>(Queue.size());

        for (int i = 0; i < Count; ++i) {
            int Top = Queue.front();
            Queue.pop();

            if (Top == End)
                return Step;

            // 주사위 1~6
            for (int j = 1; j <= 6; ++j) {
                int Next = Top + j;

                if (Next > End)
                    break;

                // 번호를 2차원 좌표로 변환
                int Row = (Next - 1) / Size;
                int Col = (Next - 1) % Size;

                if (Row % 2 == 1)
                    Col = Size - 1 - Col;

                Row = Size - 1 - Row;

                // 뱀 또는 사다리가 존재하면 이동
                if (board[Row][Col] != -1)
                    Next = board[Row][Col];

                if (Visited[Next])
                    continue;

                Visited[Next] = true;
                Queue.push(Next);
            }
        }

        Step++;
    }

    return -1;
}

int snakesAndLadders(vector<vector<int>>& board) {
    int Size = static_cast<int>(board.size());
    if (Size == 2) return 1;
    return BFS(board);
}