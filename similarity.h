#pragma once
#include <unordered_map>
#include <string>

class Similarity {
public:
    static double calculate(const std::unordered_map<std::string, int>& freq1,
        const std::unordered_map<std::string, int>& freq2);
    static std::unordered_map<std::string, int> computeFrequency(const std::vector<std::string>& ngrams);
};
