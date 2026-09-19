#include <iostream>
#include <vector>

int main() {
    int numberOfPlaces;
    std::cin >> numberOfPlaces;
    std::vector<int> guests(numberOfPlaces);

    for (int i = 0; i < numberOfPlaces; ++i) {
        int place;
        std::cin >> place;
        guests[place-1] = i + 1;
    }

    for (int i = 0; i < numberOfPlaces; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << guests[i];
    }
    std::cout << '\n';

    return 0;
}