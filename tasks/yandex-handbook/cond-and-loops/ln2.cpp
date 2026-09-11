#include <iostream>

int main() {
    int step; 
    std::cin >> step;

    double result = 0.0;

    for (int i = 1; i <= step; ++i) {
        switch (i % 2) {
            case 1: 
                // можно было result += 1 / static_cast<double>(i); 
                result += 1.0 / i;
                break;
            case 0:
                result -= 1.0 / i;
                break;
        }
    }

    std::cout << result;

    return 0;
}