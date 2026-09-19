#include <iomanip>
#include <iostream>

int main() {
    int firstWeekday, monthAmount;
    std::cin >> firstWeekday >> monthAmount;

    int totalCells = (firstWeekday - 1) + monthAmount;
    int weeks = (totalCells + 6) / 7;

    for (int week = 0, currentDay = 1; week < weeks; ++week) {
        for (int col = 1; col <= 7; ++col) {
            bool isLeadingBlank = (week == 0) && (col < firstWeekday);

            if (col > 1)
                std::cout << " "; // в первый день не пишем пробел слева

            if (isLeadingBlank) {
                std::cout << "  ";
            } else if (currentDay <= monthAmount) {
                std::cout << std::setw(2) << currentDay;
                ++currentDay;
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}