#include "similarity.h"
#include <cmath>

using namespace std;

unordered_map<string, int> Similarity::computeFrequency(const vector<string>& ngrams) {
    unordered_map<string, int> freq;
    for (const auto& gram : ngrams) freq[gram]++;
    return freq;
}

double Similarity::calculate(const unordered_map<string, int>& freq1,
    const unordered_map<string, int>& freq2) {
    double dot = 0.0, mag1 = 0.0, mag2 = 0.0;

    for (const auto& [k, v1] : freq1) {
        if (freq2.count(k)) dot += v1 * freq2.at(k);
        mag1 += v1 * v1;
    }
    for (const auto& [k, v2] : freq2) mag2 += v2 * v2;

    constexpr double epsilon = 1e-9;
    return (mag1 < epsilon || mag2 < epsilon) ? 0.0 : dot / (sqrt(mag1) * sqrt(mag2));
}