// https://cses.fi/problemset/task/1091/
// Week 2 Day 6
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int Tickets = 0, Customers = 0;
    std::cin >> Tickets >> Customers;
    
    int TicketPrices = 0, OrderPrice = 0;
    std::multiset<int> TicketList;
    while (Tickets-- && std::cin >> TicketPrices) {
        TicketList.emplace(TicketPrices);
    }
    
    std::vector<int> OrderList;
    while (Customers-- && std::cin >> OrderPrice) {
        OrderList.emplace_back(OrderPrice);
    }
    
    for (const auto& Order : OrderList) {
        auto iter = TicketList.upper_bound(Order);
        if (iter == TicketList.begin()) {
            std::cout << "-1" << "\n";
        }
        else {
            std::cout << *(--iter) << "\n";
            TicketList.erase(iter);
        }
    }
    
    return 0;
}
