//
// Created by Lucas Tai on 4/2/22.
//

#include "StringFormatter.h"

std::string StringFormatter::Trim(std::string sourceCode, type t) {
    std::string trimmedCode;
    switch(t) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            break;
        }
        case PROCEDURE: {
            trimmedCode = "";
            break;
        }
        case EXPRESSION: {
            trimmedCode = "";
            break;
        }
    }
    return trimmedCode;
}
