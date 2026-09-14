#include <iostream>
#include <cstdint>
#include <vector>

void Task1083() {
    // Task : https://cses.fi/problemset/task/1083/
    uint32_t MaxNumber = 0;
    std::cin >> MaxNumber;
    
    std::vector<uint32_t> NumberList;
    NumberList.resize(MaxNumber+1, 1);
    uint32_t Numb = 0;
    while (std::cin>>Numb)
    {
        NumberList[Numb] = 0;
    }
    
    for (uint32_t i = 1; i <= MaxNumber; ++i)
    {
        if (NumberList[i] != 0)
        {
            std::cout << i << " ";
        }
    }
}

int main(){
    Task1083();
    return 0;
}