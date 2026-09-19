#include <string>
#include <vector>

std::string CommonPrefix(const std::vector<std::string>& words) {
    if (words.empty()) {
        return "";
    }

    for (size_t i = 0; i < words[0].size(); ++i) {
        char cur_char = words[0][i];

        for (const std::string& word : words) {
            if (i >= word.size() || word[i] != cur_char)
                return words[0].substr(0, i);
        }
    }

    return words[0];
}
