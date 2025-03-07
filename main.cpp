#include "text_processor.h"
#include "similarity.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// �ļ���ȡ����
string readFile(const string& path) {
    ifstream file(path, ios::binary);
    if (!file) throw runtime_error("�޷����ļ�: " + path);
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// �ļ�д�뺯��
void writeResult(const string& path, double similarity) {
    ofstream out(path);
    if (!out) throw runtime_error("�޷�д���ļ�: " + path);
    out << fixed << setprecision(2) << similarity;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            cerr << "�÷�: " << argv[0] << " <ԭ���ļ�> <��Ϯ���ļ�> <����ļ�>\n";
            return 1;
        }

        const string origContent = readFile(argv[1]);
        const string plagContent = readFile(argv[2]);

        const int n = 2; // n-gram���ڴ�С
        auto origTokens = TextProcessor::preprocess(origContent);
        auto plagTokens = TextProcessor::preprocess(plagContent);

        auto origNGrams = TextProcessor::generateNGrams(origTokens, n);
        auto plagNGrams = TextProcessor::generateNGrams(plagTokens, n);

        auto freqOrig = Similarity::computeFrequency(origNGrams);
        auto freqPlag = Similarity::computeFrequency(plagNGrams);

        double similarity = Similarity::calculate(freqOrig, freqPlag);
        writeResult(argv[3], similarity);

    }
    catch (const exception& e) {
        cerr << "����: " << e.what() << endl;
        return 1;
    }
    return 0;
}