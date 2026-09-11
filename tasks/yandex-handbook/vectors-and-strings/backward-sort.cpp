#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> collection;
    collection.reserve(1000);

    for (std::string line; std::getline(std::cin, line);) {
        collection.push_back(line);
    }

    std::sort(collection.rbegin(), collection.rend());

    for (const auto& str : collection) {
        std::cout << str << '\n';
    }
}