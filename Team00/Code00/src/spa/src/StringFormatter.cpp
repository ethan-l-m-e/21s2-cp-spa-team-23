//
// Created by Lucas Tai on 4/2/22.
//
#include <iostream>
#include <regex>
#include "StringFormatter.h"
#include "Constants/Constants.h"

using namespace std;

string ltrim(string);
string rtrim(string);
// Return index of closing bracket given the index of the starting bracket.
// Return -1 if not found.
int findMatchingBracket(const std::string& sourceCode, int startPos) {
    int bracketCheck = 1;
    int endPos = -1;
    for (int i = startPos+1; i < sourceCode.length(); i++) {
        char c = sourceCode[i];
        switch (sourceCode[i]) {
            case('}'): {
                bracketCheck--;
                if (bracketCheck == 0) {
                    endPos = i+1;
                    goto exit_loop;
                }
                continue;
            }
            case('{'): {
                bracketCheck++;
            }
        }
    }
    exit_loop:;
    return endPos;
}
vector<string> StringFormatter::Trim(std::string sourceCode, int type) {
    string trimmedCode;
    vector<string> v;
    //Partition finalStrings = Partition();
    switch(type) {
    case ASSIGN: case READ: case PRINT: { // Case for single line stmts
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            string codeToRecurse;
            if (pos == -1)
                codeToRecurse = "";     //empty string for latter half
            else
                codeToRecurse = sourceCode.substr(pos + 1,sourceCode.size()); // +1 to get rid of the \n space
            v.push_back(trimmedCode);
            v.push_back(codeToRecurse);
            break;
        }
        case WHILE: {
            int startBracket = sourceCode.find("{");
            int bracketCheck = 1;
            int endPos = findMatchingBracket(sourceCode, startBracket);
            if (endPos == -1) {
                throw "StringFormatter failed to find matching bracket";
            }
            trimmedCode = sourceCode.substr(0, endPos);
            string codeToRecurse = removeTrailingSpace(sourceCode.substr(endPos, sourceCode.size() - trimmedCode.size()));
            v.push_back(trimmedCode);
            v.push_back(codeToRecurse);
            break;
        }
        case IF_ELSE: {
            int firstStartBracket = sourceCode.find('{');
            int secondStartBracket = sourceCode.substr(firstStartBracket + 1).find('{');
            int endPos = findMatchingBracket(sourceCode, secondStartBracket);
            trimmedCode = sourceCode.substr(0, endPos);
            string codeToRecurse = removeTrailingSpace(
                    sourceCode.substr(endPos, sourceCode.size() - trimmedCode.size()));
            v.push_back(trimmedCode);
            v.push_back(codeToRecurse);
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
        default: {
            throw "dk what to trim";
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

    char * sourceAsChar = new char[spaced.size()];
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



string StringFormatter::extractFrontStringByRegex(string sourceCode, string regex) {
    char * sourceAsChar = new char[100];
    char * regexChar = new char[100];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    string s(token);
    return s;
}

string StringFormatter::extractSecondStringByRegex(string sourceCode, string regex) {
    char * sourceAsChar = new char[100];
    char * regexChar = new char[100];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    token = strtok(NULL, regexChar);
    string s(token);
    return s;
}
