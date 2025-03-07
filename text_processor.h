#pragma once
#include <vector>
#include <string>

class TextProcessor {
public:
    static std::vector<std::string> preprocess(const std::string& content);
    static std::vector<std::string> generateNGrams(const std::vector<std::string>& tokens, int n);
};
