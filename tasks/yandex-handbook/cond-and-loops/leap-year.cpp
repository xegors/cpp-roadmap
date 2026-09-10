#include <iostream>

int main() {
    int year; 
    bool isLeapYear = false;
    std::cin >> year;

    if (year % 400 == 0) {
        isLeapYear = true;
    } else if (year % 100 == 0) {
        isLeapYear = false;
    } else if (year % 4 == 0) {
        isLeapYear = true;
    }

    isLeapYear ? std::cout << "YES" : std::cout << "NO";

    return 0;
}