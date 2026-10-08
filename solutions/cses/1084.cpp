// https://cses.fi/problemset/task/1084/
// Week 4 Day 3
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int Result = 0;
    
    int Applicants = 0, Apartments = 0, Difference = 0;
    std::cin >> Applicants >> Apartments >> Difference;
    
    int ApartValue = 0, PurchaseValue = 0;
    std::vector<int> ApartmentsList, ApplicantsList;
    
    while (Applicants-- && std::cin >> PurchaseValue) {
        ApplicantsList.push_back(PurchaseValue);
    }
    std::sort(ApplicantsList.begin(), ApplicantsList.end());
    
    while (Apartments-- && std::cin >> ApartValue) {
        ApartmentsList.push_back(ApartValue);
    }
    std::sort(ApartmentsList.begin(), ApartmentsList.end());
    
    
    
    int ApartPTR = 0, ApplicantPTR = 0;
    while (ApartPTR < ApartmentsList.size() && ApplicantPTR < ApplicantsList.size()) {
        if (ApartmentsList[ApartPTR] < ApplicantsList[ApplicantPTR] - Difference) {
            ApartPTR++;
        }
        else if (ApartmentsList[ApartPTR] > ApplicantsList[ApplicantPTR] + Difference) {
            ApplicantPTR++;
        }
        else {
            ApartPTR++;
            ApplicantPTR++;
            Result++;
        }
    }
    
    std::cout << Result << "\n";
    return 0;
}
