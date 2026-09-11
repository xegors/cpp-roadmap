#include <iostream>

int main() {
    int num, result = 0; 
    std::cin >> num;

    for (; num > 0; num /= 10) {
        result += num % 10;
    }

    std::cout << result;
    return 0;
}