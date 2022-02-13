//
// Created by Tianyi Wang on 2/2/22.
//

#ifndef SPA_ARGUMENT_H
#define SPA_ARGUMENT_H

#include <string>

enum class ArgumentType {
    SYNONYM,
    IDENT,
    STMT_NO,
    UNDERSCORE,
    PARTIALUNDERSCORE,
    EXPRESSION
};

typedef struct Argument {
    ArgumentType argumentType;
    std::string argumentValue;
} Argument;

#endif //SPA_ARGUMENT_H