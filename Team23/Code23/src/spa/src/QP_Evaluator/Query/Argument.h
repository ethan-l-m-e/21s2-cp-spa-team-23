//
// Created by Tianyi Wang on 2/2/22.
//

#ifndef SPA_ARGUMENT_H
#define SPA_ARGUMENT_H

#include <string>
#include <variant>

using std::pair;
using std::string;
using std::variant;

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

using ArgumentValue = variant<string, pair<string, AttrName>>;

typedef struct Argument {
    ArgumentType argumentType;
    ArgumentValue argumentValue;
} Argument;

#endif //SPA_ARGUMENT_H