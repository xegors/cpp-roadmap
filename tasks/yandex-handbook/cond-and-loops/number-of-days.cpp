#include <iostream>

int main() {
    int year, month;
    std::cin >> month >> year;

    switch (month) {
    case 2: { // если февраль, то нужпо проверить не високосный ли год
        bool isLeapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        std::cout << (isLeapYear ? 29 : 28);
        break;
    }

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        std::cout << 31;
        break;

    default:
        std::cout << 30;
        break;
    }

    return 0;
}