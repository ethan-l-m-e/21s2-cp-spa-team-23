//
// Created by Lucas Tai on 4/2/22.
//

#ifndef SPA_STRINGFORMATTER_H
#define SPA_STRINGFORMATTER_H
#include <string>
#include <Partition.h>

using namespace std;

class StringFormatter {
    public:
        static vector<string> Trim(std::string sourceCode, int type);
        static string removeTrailingSpace(string);
        static string extractFrontStringByRegex(string, string);

    static vector<string> tokenizeByRegex(string code, string regex);

    static string removeFrontBackBrackets(const string s);
};


#endif //SPA_STRINGFORMATTER_H
