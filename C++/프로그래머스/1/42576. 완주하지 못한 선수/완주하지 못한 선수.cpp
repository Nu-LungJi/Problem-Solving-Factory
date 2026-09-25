#include <string>
#include <vector>
#include <set>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    std::multiset<string> Container;
    for (const auto& Element : participant){
        Container.emplace(Element);
    }
    
    for (const auto& Element : completion){
        auto iter = Container.find(Element);
        if (iter != Container.end()){
            Container.erase(iter);
        }
    }
    string Result = "";
    for (const auto& Element : Container){
        Result = Element;
    }
    return Result;
}