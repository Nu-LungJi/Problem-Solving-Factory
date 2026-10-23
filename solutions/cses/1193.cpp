// https://cses.fi/problemset/task/1193/
// Week 6 Day 4
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<std::string> labyrinth;
int Height = 0, Width = 0;
int StartX, StartY, EndX, EndY;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int ds[] = {'U', 'D', 'L', 'R'};

int dir[1000][1000];

bool BFS() {
    std::queue<std::pair<int, int>> Queue;
    Queue.push({StartX, StartY});
    std::vector<std::vector<bool>> Visited(Height, std::vector<bool>(Width, false));
    Visited[StartX][StartY] = true;
    
    while (!Queue.empty()) {
        std::pair<int, int> Top = Queue.front();
        Queue.pop();
        
        if (Top.first == EndX && Top.second == EndY) return true;
        
        for (int i = 0; i < 4; ++i) {
            int X = Top.first + dx[i];
            int Y = Top.second+ dy[i];
            if (X >= 0 && X < Height && Y >= 0 && Y < Width)
            {
                if (!Visited[X][Y] && labyrinth[X][Y] != '#') {
                    Visited[X][Y] = true;
                    dir[X][Y] = i;
                    Queue.push({X, Y});
                }
            }
        }
    }
    
    return false;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> Height >> Width;
    
    labyrinth.resize(Height);
    for (int i = 0; i < Height; ++i) {
        std::cin >> labyrinth[i];
        for (int j = 0; j < Width; ++j) {
            if (labyrinth[i][j] == 'A') {
                StartX = i; StartY = j;
            }
            if (labyrinth[i][j] == 'B') {
                EndX = i; EndY = j;
            }
        }
    }
    
    if (!BFS()) {
        std::cout << "NO" << "\n";
        return 0;
    }
    
    std::string Direction;
    int cx = EndX, cy = EndY;
    while (!(cx == StartX && cy == StartY)) {
        int d = dir[cx][cy];
        Direction += ds[d];
        cx -= dx[d];
        cy -= dy[d];
    }
    
    std::cout << "YES" << "\n";
    std::reverse(Direction.begin(), Direction.end());
    std::cout << Direction.size() << "\n";
    std::cout << Direction;
    
    return 0;
}
