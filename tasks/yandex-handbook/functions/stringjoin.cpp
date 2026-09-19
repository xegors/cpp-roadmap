#include <iostream>
#include <string>
#include <vector>

std::string Join(const std::vector<std::string>& tokens, char delimeter) {
    switch (tokens.size()) {
    case 0:
        return "";
    case 1:
        return tokens[0];
    }

    std::string joined = "";
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i == tokens.size() - 1) {
            joined += tokens[i];
            break;
        }

        joined += tokens[i] + delimeter;
    }

    return joined;
}

int main() {
    std::cout << Join({"What", "is", "your", "_", "name?", "", "_"}, '_') << '\n';
}
