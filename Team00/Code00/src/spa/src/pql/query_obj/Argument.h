//
// Created by Tianyi Wang on 2/2/22.
//

#include <string>

#ifndef SPA_ARGUMENT_H
#define SPA_ARGUMENT_H

#endif //SPA_ARGUMENT_H


enum class ArgumentType {
    SYNONYM,
    IDENT,
    STMT_NO,
    UNDERSCORE,
    EXPRESSION
};

typedef struct Argument {
    ArgumentType argumentType;
    std::string argumentValue;
};