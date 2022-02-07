//
// Created by Tin Hong Wen on 6/2/22.
//
#include <string>
#include <regex>
#include <iostream>

#include "SourceTokenizer.h"
#include "StringFormatter.h"

using namespace std;

void SourceTokenizer::extractAssign(string sourceCode, vector<string> &v) {
    int equal = sourceCode.find('=');
    int end = sourceCode.find(';');
    string varname = sourceCode.substr(0, equal);
    string expr = sourceCode.substr(equal + 1, end - equal - 1);
    varname = StringFormatter::removeTrailingSpace(varname);
    expr = StringFormatter::removeTrailingSpace(expr);
    v.push_back(varname);
    v.push_back(expr);
}