//
// Created by Lucas Tai on 4/2/22.
//

#include "StringFormatter.h"
#include "Constants.h"
std::string StringFormatter::Trim(std::string sourceCode, int type, std::string* initCode) {
    std::string trimmedCode;
    switch(type) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            std::string codeToRecurse = sourceCode.substr(pos,sourceCode.size());
            initCode = &codeToRecurse;
            break;
        }
        case PROCEDURE: {
            trimmedCode = "";
            break;
        }
        case BASE_CASE: {
            trimmedCode = "";
            break;
        }
    }
    return trimmedCode;
}
