#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <cstdint>
using namespace std;

vector<int> PaperList;
array<bool, 7> CheckList{false};

void Recur(string& numbers, string& Case, int Start, int Count) {
    if (Count == 0){
        if (Case[0] == '0') return;
        int Value = stoi(Case);
        for (const auto& Element : PaperList) {
            if (Element == Value) return;
        }
        PaperList.emplace_back(Value);
        return;
    }
    
    for (size_t i = Start; i < numbers.size(); ++i) {
        if (CheckList[i]) continue;
        Case += numbers[i];
        CheckList[i] = true;
        Recur(numbers, Case, 0, Count - 1);
        CheckList[i] = false;
        Case.pop_back();
    }
}
int solution(string numbers) {
    string Case;
    for (size_t i = 1; i <= numbers.size(); ++i) {
        Recur(numbers, Case, 0, i);
    }
    
    int FinalCount = 0 ;
    for (const auto& Element : PaperList){
        vector<uint8_t> NumbCheck(Element + 1, false);
        NumbCheck[1] = true;
        for (int i = 2; i <= sqrt(Element); ++i){
            if (NumbCheck[i]) continue;
            for (int j = 2; i * j <= Element; ++j){
                NumbCheck[i * j] = true;
            }
        }
        if (!NumbCheck[Element]) FinalCount++;
    }
    
    return FinalCount;
}