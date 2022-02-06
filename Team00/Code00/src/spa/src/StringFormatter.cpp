//
// Created by Lucas Tai on 4/2/22.
//

#include "StringFormatter.h"
#include "Constants.h"
Partition StringFormatter::Trim(std::string sourceCode, int type) {
    std::string trimmedCode;
    Partition finalStrings = Partition();
    switch(type) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            std::string codeToRecurse = sourceCode.substr(pos,sourceCode.size());
            finalStrings = Partition(trimmedCode,codeToRecurse);
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
    return finalStrings;
}
