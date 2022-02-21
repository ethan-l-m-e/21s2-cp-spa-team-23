//
// Created by Lucas Tai on 4/2/22.
//

#ifndef SPA_STRINGFORMATTER_H
#define SPA_STRINGFORMATTER_H
#include <string>

using namespace std;

class StringFormatter {
    public:
        static vector<string> partitionAccordingToCase(std::string sourceCode, int type);
        static string removeTrailingSpace(string);
        static string extractFrontStringByRegex(string, string);
        static string extractSecondStringByRegex(string, string);
        static vector<string> tokenizeByRegex(string code, string regex);
        static string removeFrontBackBrackets(const string s);
        static string removeMatchingFrontBackBrackets(const string& s);
        static vector<string> partitionBasedOnParentheses(string sourceCode, string brackets);
        static vector<string> partitionBySemiColon(string sourceCode);
};


#endif //SPA_STRINGFORMATTER_H
