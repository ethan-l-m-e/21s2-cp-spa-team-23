//
// Created by Lucas Tai on 4/2/22.
//

#include "StringFormatter.h"
#include "Constants/Constants.h"
Partition StringFormatter::Trim(std::string sourceCode, int type) {
    std::string trimmedCode;
    Partition finalStrings = Partition();
    switch(type) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            std::string codeToRecurse = sourceCode.substr(pos + 1,sourceCode.size()); // +1 to get rid of the \n space
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
