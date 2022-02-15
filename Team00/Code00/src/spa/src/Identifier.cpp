//
// Created by Tin Hong Wen on 2/2/22.
//
#include <iostream>
#include <regex>
#include <vector>
#include <string>

#include "Identifier.h"
#include "Constants/regex.h"
#include "Constants/Constants.h"
#include "Validator.h"
#include "StringFormatter.h"

int switchCaseOrError(int, bool);

int Identifier::identifyFirstObject(string sourceCode) {
    // TODO: IDENTIFIER (+ validator) CLASS to determine object/node type. if identified, check if the basic syntax holds
    string firstLine = StringFormatter::extractFrontStringByRegex(sourceCode, "\n");
    firstLine = StringFormatter::removeTrailingSpace(firstLine);
    if(regex_match(firstLine, std::regex(PROCEDURE_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(PROCEDURE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(ASSIGN_IDENTIFIER))) {
        return ASSIGN; // ignores EXPR_TERM
    } else if (regex_match(firstLine, std::regex(READ_REGEX))) {
        return READ; // done
    } else if (regex_match(firstLine, std::regex(PRINT_REGEX))) {
        return PRINT; // done
    } else if (regex_match(firstLine, std::regex(WHILE_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesClosure(sourceCode, "()") && Validator::checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(WHILE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(IF_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesClosure(sourceCode, "()") && Validator::checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(IF_ELSE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(EXPR_TERM_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesClosure(sourceCode, "()");
        return switchCaseOrError(EXPR_TERM, isCorrect); //ignores stmtLst
    } /*else if (regex_match(firstLine, std::regex(COND_EXPR_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesClosure(sourceCode, "()");
        return switchCaseOrError(COND_EXPR, isCorrect);
    }*/ else if (regex_match(firstLine, std::regex(VAR_NAME))) {
        return VARIABLE_NAME; // same as proc name
    }  else if (regex_match(firstLine, std::regex(CONST_VALUE))) {
        return CONSTANT_VALUE;
    } else {
        cout << "parser cannot identify '" + firstLine + "' in the source code\n";
        return ERROR;
    }
}


int switchCaseOrError(int switchCase, bool cond) {
    if (cond)  return switchCase;
    else return ERROR;
}