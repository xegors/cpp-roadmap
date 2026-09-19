#include <iostream>
#include <cctype>
#include <string>

int main() {
    std::string password;
    std::getline(std::cin, password);
    bool upper = false, lower = false, digit = false, punct = false;

    if (!(password.size() >= 8 && password.size() <= 14)) {
        std::cout << "NO";
        return 0;
    }

    for (auto sym : password){
        if (std::isdigit(sym)) digit = true;
        else if (std::isupper(sym)) upper = true;
        else if (std::islower(sym)) lower = true;
        else if (std::ispunct(sym)) punct = true;
        else {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << (int(upper) + int(lower) + int(digit) + int(punct) >= 3 ? "YES" : "NO");

    return 0;
}