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
vector<string> StringFormatter::Trim(std::string sourceCode, int type) {
    string trimmedCode;
    vector<string> v;
    //Partition finalStrings = Partition();
    switch(type) {
        case ASSIGN:{
            int pos = sourceCode.find('\n');
            trimmedCode = sourceCode.substr(0, pos);
            string codeToRecurse;
            if (pos == -1)
                codeToRecurse = "";     //empty string for latter half
            else
                codeToRecurse = sourceCode.substr(pos + 1,sourceCode.size()); // +1 to get rid of the \n space

            v.push_back(trimmedCode);
            v.push_back(codeToRecurse);
            //finalStrings = Partition(trimmedCode,codeToRecurse);
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


vector<string> StringFormatter::tokenizeByRegex(string s, string regex) {
    std::regex r(regex);
    string spaced = std::regex_replace(s, r, " ");

    char * sourceAsChar = new char[spaced.size()];
    char * regexChar = "[ ]*";
    strcpy(sourceAsChar, spaced.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    vector<string> v;
    while (token) {
        cout << token << "\n";
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


