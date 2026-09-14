#include <iostream>
#include <cstdint>

void Task1068() {
    // Task : https://cses.fi/problemset/task/1068/
    uint64_t element = 0;
    std::cin >> element;
    
    while (true)
    {
        std::cout << element << " ";
        if      (element == 1)   break;
        else if (element % 2 == 0)  element /= 2;
        else    element = element * 3 + 1;
    }
}

int main(){
    Task1068();
    return 0;
}