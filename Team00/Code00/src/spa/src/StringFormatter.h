//
// Created by Lucas Tai on 4/2/22.
//

#ifndef SPA_STRINGFORMATTER_H
#define SPA_STRINGFORMATTER_H
#include <string>
enum type {
    ASSIGN, PROCEDURE, EXPRESSION
};
class StringFormatter {
    public:
        std::string Trim(std::string sourceCode,type t,std::string* initCode);
};


#endif //SPA_STRINGFORMATTER_H
