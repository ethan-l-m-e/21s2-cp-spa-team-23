//
// Created by Lucas Tai on 4/2/22.
//
#include <iostream>

#include "StringFormatter.h"
#include "Constants/Constants.h"

using namespace std;

Partition StringFormatter::Trim(std::string sourceCode, int type) {
    string trimmedCode;
    Partition finalStrings = Partition();
    switch(type) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            string codeToRecurse;
            if (pos == -1)      codeToRecurse = "";     //empty string for latter half
            else       codeToRecurse = sourceCode.substr(pos + 1,sourceCode.size()); // +1 to get rid of the \n space
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
