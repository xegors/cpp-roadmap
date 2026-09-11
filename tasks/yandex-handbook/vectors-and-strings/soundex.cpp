#include <iostream>
#include <string>

int main() {
    std::string word;
    std::cin >> word;

    constexpr size_t kLen = 4;
    std::string res;
    res.reserve(kLen);
    res += word[0];

    for (size_t i = 1; i < word.size() && res.size() < kLen; ++i) {
        char code = 0;
        switch (word[i]) {
            case 'a': case 'e': case 'h': case 'i': 
            case 'o': case 'u': case 'w': case 'y':
                continue;

            case 'b': case 'f': case 'p': case 'v': 
                code = '1'; 
                break;
            case 'c': case 'g': case 'j': case 'k': 
            case 'q': case 's': case 'x': case 'z': 
                code = '2'; 
                break;

            case 'd': case 't': 
                code = '3'; 
                break;

            case 'l': 
                code = '4'; 
                break;

            case 'm': case 'n': 
                code = '5'; 
                break;
            case 'r': 
                code = '6'; 
                break;
        }

        if (code != res.back()) {
            res += code;
        }
    }

    res.resize(kLen, '0');
    std::cout << res;
}