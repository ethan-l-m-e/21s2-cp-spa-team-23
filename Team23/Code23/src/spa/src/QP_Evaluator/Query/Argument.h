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
    PARTIAL_UNDERSCORE,
    EXPRESSION,
    ATTR_REF,
    BOOLEAN
};

enum class AttrName {
    PROC_NAME,
    VAR_NAME,
    VALUE,
    STMT_NO,
};

using ArgumentValue = std::variant<std::string, std::pair<std::string, AttrName>>;

typedef struct Argument {
    ArgumentType argumentType;
    ArgumentValue argumentValue;
} Argument;

#endif //SPA_ARGUMENT_H