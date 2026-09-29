#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    int TileRow = 3, TileCol = 0;
    vector<int> Result;
    int WholeTile = brown + yellow;
    while (true) {
        if (WholeTile % TileRow == 0){
            TileCol = WholeTile / TileRow;
            if (yellow == (TileRow - 2) * (TileCol - 2)){
                Result.emplace_back(TileCol);
                Result.emplace_back(TileRow);

                break;
            }
        }
        TileRow++;
    }
    
    return Result;
}