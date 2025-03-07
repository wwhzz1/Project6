#include "text_processor.h"
#include <cctype>

using namespace std;

vector<string> TextProcessor::preprocess(const string& content) {
    vector<string> tokens;
    size_t i = 0;
    while (i < content.size()) {
        // UTF-8字符长度判断
        int len = 1;
        unsigned char c = content[i];
        if ((c & 0x80) != 0) {
            if ((c & 0xE0) == 0xC0) len = 2;
            else if ((c & 0xF0) == 0xE0) len = 3;
            else if ((c & 0xF8) == 0xF0) len = 4;
        }

        // 提取字符并过滤空白
        string ch = content.substr(i, len);
        if (!(ch.size() == 1 && isspace(ch[0]))) {
            tokens.push_back(ch);
        }
        i += len;
    }
    return tokens;
}

vector<string> TextProcessor::generateNGrams(const vector<string>& tokens, int n) {
    vector<string> ngrams;
    if (tokens.size() < n) return ngrams;

    for (size_t i = 0; i <= tokens.size() - n; ++i) {
        string gram;
        for (int j = 0; j < n; ++j) {
            gram += tokens[i + j];
        }
        ngrams.push_back(gram);
    }
    return ngrams;
}