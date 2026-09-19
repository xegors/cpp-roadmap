#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a < b) {
        std::swap(a, b);
    }
    if (a < c) {
        std::swap(a, c);
    }

    if (a * a == b * b + c * c) {
        std::cout << "YES";
    } else if (a >= b + c) {
        std::cout << "UNDEFINED";
    } else {
        std::cout << "NO";
    }

    return 0;
}