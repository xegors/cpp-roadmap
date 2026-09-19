#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string& str, char delimeter) {
    if (str == "")
        return {""};

    std::vector<std::string> splited;
    splited.reserve(str.size());

    std::string word = "";
    for (const char cur : str) {
        if (cur == delimeter) {
            splited.push_back(word);
            word = "";
        } else {
            word += cur;
        }
    }

    splited.push_back(word);

    return splited;
}

int main() {
    std::vector<std::string> splited = Split("---123---", '-');
    std::cout << splited.size() << '\n';

    for (const std::string& word : splited)
        std::cout << word << '\n';
}
