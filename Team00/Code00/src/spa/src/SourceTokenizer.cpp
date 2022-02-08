//
// Created by Tin Hong Wen on 6/2/22.
//
#include <string>
#include <regex>
#include <iostream>
#include <stack>

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
void SourceTokenizer::extractIfElseThen(string sourceCode, vector<string> &v) {
    int then = sourceCode.find("then");
    int firstIf = sourceCode.find("if");
    string cond = sourceCode.substr(firstIf+2, then-firstIf-2); //extracts the condition with brackets and whitespaces
    cond = StringFormatter::removeTrailingSpace(cond);
    cond = StringFormatter::removeFrontBackBrackets(cond); //removes the brackets
    v.push_back(cond);
    sourceCode = sourceCode.substr(then+4,sourceCode.length()-then-4);
    int elseCheckCounter = 1;
    int posOfElse = 0;
    string temp = sourceCode;
    //while loop to check for if-else nesting
    while(elseCheckCounter != 0) {
        int nextElse = temp.find("else") + 4;
        int nextIf = temp.find("if");
        if (nextIf == string::npos) {
            elseCheckCounter--;
        } else if (nextIf > nextElse) {
            elseCheckCounter--;
        }
        posOfElse += nextElse;
        temp = temp.substr(nextElse, temp.length() - nextElse); //removes the first instance of nested if else pair
//        cout<< temp;
//        cout<<"||";
    }

    string ifBlock = sourceCode.substr(0,posOfElse-4);
    ifBlock = StringFormatter::removeFrontBackBrackets(ifBlock);
    string elseBlock = sourceCode.substr(posOfElse,sourceCode.length()-posOfElse);
    elseBlock = StringFormatter::removeFrontBackBrackets(elseBlock);
    v.push_back(ifBlock);
    v.push_back(elseBlock);

}

void SourceTokenizer::extractWhile(string sourceCode, vector<string> &v) {
    int startOfCond = sourceCode.find("while")+5;
    int endOfCond = sourceCode.find('{');
    string cond = sourceCode.substr(startOfCond, endOfCond-startOfCond);
    cond = StringFormatter::removeFrontBackBrackets(cond);
    v.push_back(cond);
    string bodyOfWhile = sourceCode.substr(endOfCond,sourceCode.length()-endOfCond);
    bodyOfWhile = StringFormatter::removeFrontBackBrackets(bodyOfWhile);
    v.push_back(bodyOfWhile);
}

void SourceTokenizer::extractProcedure(string sourceCode, vector<string> &v) {
    int start = sourceCode.find('{');
    int end = sourceCode.find('}');
    string procedureName = sourceCode.substr(10, start-10);
    string procedureCode = sourceCode.substr(start+1, end-start-1);
    procedureName = StringFormatter::removeTrailingSpace(procedureName);
    v.push_back(procedureName);
    v.push_back(procedureCode);
}

void SourceTokenizer::extractExpression(string sourceCode, vector<string> &v) {
    stack<char> parenthesesStack;
    for (int i = sourceCode.length(); i>0;i--){
        switch(sourceCode[i-1]){
            case '+':
                if(parenthesesStack.empty()){

                }
                break;
            case '-':
                if(parenthesesStack.empty()){

                }

                break;

        }
    }
    int equal = sourceCode.rfind('=');
    int end = sourceCode.find(';');
    string varname = sourceCode.substr(0, equal);
    string expr = sourceCode.substr(equal + 1, end - equal - 1);
    varname = StringFormatter::removeTrailingSpace(varname);
    expr = StringFormatter::removeTrailingSpace(expr);
    v.push_back(varname);
    v.push_back(expr);
}
