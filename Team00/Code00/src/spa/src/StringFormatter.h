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
};


#endif //SPA_STRINGFORMATTER_H
