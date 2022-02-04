//
// Created by Lucas Tai on 4/2/22.
//

#ifndef SPA_STRINGFORMATTER_H
#define SPA_STRINGFORMATTER_H
#include <string>
enum type {
    ASSIGN, PROCEDURE, EXPRESSION
};
static class StringFormatter {
    public:
        std::string Trim(std::string sourceCode,type t);
};


#endif //SPA_STRINGFORMATTER_H
