#include <string>
#include <vector>

std::string CommonPrefix(const std::vector<std::string>& words) {
    std::string res;

    for (size_t i = 0; i < words[0].size(); ++i) {
        res = words[0].substr(0, i);
        for (const std::string& word : words) {
            if (res != word.substr(0, i))
                return res.substr(0, i-1);
        }
    }

    return res;
}