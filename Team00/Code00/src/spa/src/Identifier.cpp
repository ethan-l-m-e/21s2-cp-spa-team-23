//
// Created by Tin Hong Wen on 2/2/22.
//
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Identifier.h"
#include "Constants/regex.h"
#include "Constants/Constants.h"
#include "Validator.h"

string ltrim(const string &s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}
string rtrim(const string &s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}
string trim(const string &s) {
    return ltrim(rtrim(s));
}

string extractFrontStringByRegex(string, string);
int switchCaseOrError(int, bool);

int Identifier::identifyFirstObject(string sourceCode) {
    // TODO: IDENTIFIER (+ validator) CLASS to determine object/node type. if identified, check if the basic syntax holds
    string firstLine = extractFrontStringByRegex(sourceCode, "\n");
    firstLine = trim(firstLine);
    if(regex_match(firstLine, std::regex(PROCEDURE_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesCorrectness(sourceCode, "{}");
        return switchCaseOrError(PROCEDURE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(ASSIGN_IDENTIFIER))) {
        return ASSIGN; // ignores EXPR_TERM
    } else if (regex_match(firstLine, std::regex(READ_REGEX))) {
        return READ; // done
    } else if (regex_match(firstLine, std::regex(PRINT_REGEX))) {
        return PRINT; // done
    } else if (regex_match(firstLine, std::regex(EXPR_TERM_IDENTIFIER))) {
        bool isCorrect = Validator::checkParenthesesCorrectness(sourceCode, "()");
        return switchCaseOrError(EXPR_TERM, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(VAR_NAME)) | regex_match(sourceCode, std::regex(CONST_VALUE))) {
        return BASE_CASE;
    } else {
        cout << "parser cannot identify '" + firstLine + "' in the source code";
        return ERROR;
    }
}

int switchCaseOrError(int switchCase, bool cond) {
    if (cond)  return switchCase;
    else return ERROR;
}

string extractFrontStringByRegex(string sourceCode, string regex) {
    char * sourceAsChar = new char[100];
    char * regexChar = new char[100];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    string s(token);
    return s;
}