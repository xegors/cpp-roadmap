#include <string>
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        if (word1 == "") {
            return word2;
        }
        if (word2 == "") {
            return word1;
        }

        if (word1.size() > word2.size()) {
            std::swap(word1, word2);
        }

        string res = "";
        for (size_t i = 0; i < word1.size(); ++i) {
            res += word1[i] + word2[i];
        }

        for (size_t i = word1.size(); i < word2.size(); ++i) {
            res += word2[i];
        }

        return res;
    }
};
