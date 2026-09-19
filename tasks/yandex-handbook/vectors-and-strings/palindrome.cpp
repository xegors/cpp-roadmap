#include <iostream>
#include <string>
#include <vector>

int main() {
    constexpr size_t maxLen = 100;

    std::string raw;
    std::getline(std::cin, raw);

    std::vector<char> line;
    line.reserve(maxLen);

    for (char ch : raw) {
        if (ch != ' ')
            line.push_back(ch);
    }

    for (size_t i = 0; i < line.size() / 2; ++i) {
        if (line[i] != line[line.size() - i - 1]) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES";
    return 0;
}