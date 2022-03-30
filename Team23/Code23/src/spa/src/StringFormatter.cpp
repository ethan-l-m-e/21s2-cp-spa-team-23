//
// Created by Lucas Tai on 4/2/22.
//
#include <iostream>
#include <regex>
#include "StringFormatter.h"
#include "SourceProcessor/SourceTokenizer.h"

using namespace std;

string ltrim(string);
string rtrim(string);

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

string StringFormatter::removeMatchingFrontBackBrackets(const string& s) {
    string temp = removeTrailingSpace(s);
    while(temp[0] == '(') {
        int bracketCount = 1;
        for (int i = 1; i < temp.length(); i ++) {
            if (temp[i] == '(') {
                bracketCount++;
            } else if (temp[i] == ')') {
                bracketCount--;
            }
            if (bracketCount == 0 && (i == temp.length() -1)) {
                temp = temp.substr(1,temp.length()-2);
            } else if (bracketCount == 0) {
                return temp;
            }
        }
    }
    return temp;
}

/**
 * converts string input a vector of tokens based on regex
 * @param s
 * @param regex
 * @return
 */
vector<string> StringFormatter::tokenizeByRegex(string s, string regex) {
    std::regex rgx(regex);
    vector<string> v;
    copy( std::sregex_token_iterator(s.begin(), s.end(), rgx, -1),
              std::sregex_token_iterator(), back_inserter(v));

    vector<string>::iterator i;
    vector<string> outputVector;
    for (i = v.begin(); i != v.end(); ++i) {
        if(*i != "")
            outputVector.push_back(*i);
    }

    return outputVector;

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
            if(startedCount == true && count != 0) {
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
    char * sourceAsChar = new char[sourceCode.size() + 1];
    char * regexChar = new char[regex.size() + 1];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    string s(token);
    delete [] sourceAsChar;
    delete [] regexChar;
    return s;
}
