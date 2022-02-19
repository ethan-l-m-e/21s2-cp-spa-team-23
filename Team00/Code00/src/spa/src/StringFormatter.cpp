//
// Created by Lucas Tai on 4/2/22.
//
#include <iostream>
#include <regex>
#include "StringFormatter.h"
#include "Constants/Constants.h"
#include "SourceProcessor/SourceTokenizer.h"

using namespace std;

string ltrim(string);
string rtrim(string);
vector<string> StringFormatter::partitionAccordingToCase(std::string sourceCode, int type) {
    string trimmedCode;
    vector<string> v;
    switch(type) {
        case ASSIGN: case READ: case PRINT: {
            v = StringFormatter::partitionBySemiColon(sourceCode);
            break;
        }
        case WHILE: {
            vector<string> cond_leftover = StringFormatter::partitionBasedOnParentheses(sourceCode, "()");
            vector<string> stmtLst_leftover = StringFormatter::partitionBasedOnParentheses(cond_leftover[1], "{}");
            string reconstructedWhile = "while" + cond_leftover[0] + stmtLst_leftover[0];
            v.push_back(reconstructedWhile);
            v.push_back(stmtLst_leftover[1]);
            break;
        }
        case IF_ELSE: {
            vector<string> cond_leftover = StringFormatter::partitionBasedOnParentheses(sourceCode, "()");
            vector<string> stmtLst1_leftover = StringFormatter::partitionBasedOnParentheses(cond_leftover[1], "{}");
            vector<string> stmtLst2_leftover = StringFormatter::partitionBasedOnParentheses(stmtLst1_leftover[1], "{}");
            string reconstructedIfElse = "if" + cond_leftover[0] + "then" + stmtLst1_leftover[0]  + "else" + stmtLst2_leftover[0];
            v.push_back(reconstructedIfElse);
            v.push_back(stmtLst2_leftover[1]);
            break;
        }
        case PROCEDURE: {   // for full iteration 2/3
            string procFront = StringFormatter::extractFrontStringByRegex(sourceCode, "\\{");
            vector<string> stmtLst_leftovers = StringFormatter::partitionBasedOnParentheses(sourceCode, "{}");
            string reconstructedProcedure = procFront + stmtLst_leftovers[0];
            v.push_back(reconstructedProcedure);
            v.push_back(stmtLst_leftovers[1]);
            break;
        }
        default: {
            throw "dk what to trim. type argument is likely invalid for this method";
        }
    }
    return v;
}


string StringFormatter::removeTrailingSpace(const string s) {
    return ltrim(rtrim(s));
}

string ltrim(const string s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}
string rtrim(const string s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

string StringFormatter::removeFrontBackBrackets(const string s){
    string toReturn = removeTrailingSpace(s);
    return toReturn.substr(1,toReturn.length()-2);
}

vector<string> StringFormatter::tokenizeByRegex(string s, string regex) {

    std::regex r(regex);
    string spaced = std::regex_replace(s, r, "//");

    char * sourceAsChar = new char[spaced.size()+1];
    char * regexChar = "//*";
    strcpy(sourceAsChar, spaced.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    vector<string> v;
    while (token) {
        v.push_back(token);
        token = strtok(NULL, regexChar);
    }
    return v;
}

vector<string> StringFormatter::partitionBySemiColon(string sourceCode) {
    vector<string> v;
    int pos = sourceCode.find(';');
    string trimmedCode = sourceCode.substr(0, pos + 1);
    string codeToRecurse = sourceCode.substr(pos + 1, sourceCode.size());
    trimmedCode = StringFormatter::removeTrailingSpace(trimmedCode);
    codeToRecurse = StringFormatter::removeTrailingSpace(codeToRecurse);
    v.push_back(trimmedCode);
    v.push_back(codeToRecurse);
    return v;
}

//extracts the parentheses with the stated brackets, then put the string in front, the remaining located at the back
vector<string> StringFormatter::partitionBasedOnParentheses(string sourceCode, string brackets) {
    vector<string> v;
    string bracketedString = "";
    string leftovers;

    int count = 0;
    bool startedCount = false;
    char bracketLeft = brackets[0];
    char bracketRight = brackets[1];
    int i = 0;

    while(i < sourceCode.size()) {
        if (sourceCode[i] == bracketLeft) {
            if(startedCount == false) {
                startedCount = true;
            }
            bracketedString += sourceCode[i];
            count++;

        } else if (sourceCode[i] == bracketRight) {
            bracketedString += sourceCode[i];
            count--;
            if(count == 0) {
                break;
            }
        } else {
            if(startedCount = true && count != 0) {
                bracketedString += sourceCode[i];
            }
        }
        i++;
    }
    leftovers = sourceCode.substr(i + 1, sourceCode.size());
    bracketedString = StringFormatter::removeTrailingSpace(bracketedString);
    leftovers = StringFormatter::removeTrailingSpace(leftovers);
    v.push_back(bracketedString);
    v.push_back(leftovers);
    return v;
}



string StringFormatter::extractFrontStringByRegex(string sourceCode, string regex) {
    char * sourceAsChar = new char[100];
    char * regexChar = new char[100];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    string s(token);
    return s;
}
