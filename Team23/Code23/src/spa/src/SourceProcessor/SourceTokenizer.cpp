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

void SourceTokenizer::extractCall(string sourceCode, vector<string> &v) {
    int call = sourceCode.find("call")+4;
    int end = sourceCode.find(';');
    string procName = StringFormatter::removeTrailingSpace(sourceCode.substr(call, end - call));
    v.push_back(procName);
}

void SourceTokenizer::extractRead(string sourceCode, vector<string> &v) {
    int read = sourceCode.find("read")+4;
    int end = sourceCode.find(';');
    string varname = StringFormatter::removeTrailingSpace(sourceCode.substr(read, end - read));
    v.push_back(varname);
}

void SourceTokenizer::extractPrint(string sourceCode, vector<string> &v) {
    int print = sourceCode.find("print")+5;
    int end = sourceCode.find(';');
    string varname = StringFormatter::removeTrailingSpace(sourceCode.substr(print, end - print));
    v.push_back(varname);
}

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
    string condBlock = StringFormatter::tokenizeByRegex(sourceCode, "[ ]*if[ ]*\\(|\\)[ ]*then[ ]*\\{")[0];
    v.push_back(condBlock);

    vector<string> thenElse = StringFormatter::partitionBasedOnParentheses(sourceCode, "{}");
    string thenBlockWithBrackets = StringFormatter::removeTrailingSpace(thenElse[0]);
    int frontBracket = thenBlockWithBrackets.find("{");
    int backBracket = thenBlockWithBrackets.size() - 2;
    string thenBlock = StringFormatter::removeTrailingSpace(thenBlockWithBrackets.substr(frontBracket + 1, backBracket));

    string elseBlockWithBrackets = StringFormatter::removeTrailingSpace(StringFormatter::partitionBasedOnParentheses(thenElse[1], "{}")[0]);
    frontBracket = elseBlockWithBrackets.find("{");
    backBracket = elseBlockWithBrackets.size() - 2;

    string elseBlock = StringFormatter::removeTrailingSpace(elseBlockWithBrackets.substr(frontBracket + 1, backBracket));

    v.push_back(thenBlock);
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
    int end = sourceCode.rfind('}');
    string procedureName = sourceCode.substr(10, start-10);
    string procedureCode = sourceCode.substr(start+1, end-start-1);
    procedureName = StringFormatter::removeTrailingSpace(procedureName);
    v.push_back(procedureName);
    v.push_back(procedureCode);
}

void SourceTokenizer::extractExpression(string sourceCode, vector<string> &v) {
    int bracketCheck = 0;
    int exprPos = -1;
    while(true) {
        for (int i = sourceCode.length()-1; i >= 0; i--) {
            switch (sourceCode[i]) {
                case ('+'):
                    if (bracketCheck == 0) {
                        exprPos = i;
                        goto exit_loop;
                    }
                    break;
                case ('-'):
                    if (bracketCheck == 0) {
                        exprPos = i;
                        goto exit_loop;
                    }
                    break;
                case (')'):
                    bracketCheck++;
                    break;
                case ('('):
                    bracketCheck--;
                    break;
                default:
                    break;
            }
        }
        for (int i = sourceCode.length()-1; i >= 0; i--) {
            switch (sourceCode[i]) {
                case ('*'):
                    if (bracketCheck == 0) {
                        exprPos = i;
                        goto exit_loop;
                    }
                    break;
                case ('/'):
                    if (bracketCheck == 0) {
                        exprPos = i;
                        goto exit_loop;
                    }
                    break;
                case ('%'):
                    if (bracketCheck == 0) {
                        exprPos = i;
                        goto exit_loop;
                    }
                    break;
                case (')'):
                    bracketCheck++;
                    break;
                case ('('):
                    bracketCheck--;
                    break;
                default:
                    break;
            }
        }

        sourceCode = StringFormatter::removeFrontBackBrackets(sourceCode);
    }
        exit_loop:;

    string left = sourceCode.substr(0, exprPos);
    string right = sourceCode.substr(exprPos+1, sourceCode.length()-exprPos-1);
    string sign = sourceCode.substr(exprPos, 1);
    left = StringFormatter::removeTrailingSpace(left);
    right = StringFormatter::removeTrailingSpace(right);
    v.push_back(left);
    v.push_back(right);
    v.push_back(sign);
}



void SourceTokenizer::extractCondExpr(string sourceCode, vector<string> &v) {
    string left, right, oper;
    sourceCode = StringFormatter::removeMatchingFrontBackBrackets(sourceCode);
    if(regex_match(sourceCode, std::regex("[ ]*![ ]*\\((.*)\\)[ ]*"))) {
        int pos = sourceCode.find("!");
        sourceCode = StringFormatter::removeTrailingSpace(sourceCode.substr(pos + 1, sourceCode.size()));
        string removedBrackets = sourceCode.substr(1, sourceCode.size() - 2);
        extractCondExpr(removedBrackets, v);
    }else if(regex_match(sourceCode, std::regex("\\((.*)\\)[ ]*\\&\\&[ ]*\\((.*)\\)|\\((.*)\\)[ ]*\\|\\|[ ]*\\((.*)\\)"))) {
        vector<string> partition = StringFormatter::partitionBasedOnParentheses(sourceCode, "()");
        string front = StringFormatter::removeTrailingSpace(partition[0]);
        string opAndBack = partition[1];
        left = StringFormatter::removeTrailingSpace(front.substr(1, front.size() - 2));
        oper = opAndBack.substr(0,2);
        string back = StringFormatter::removeTrailingSpace(opAndBack.substr(2, opAndBack.size()));
        right = StringFormatter::removeTrailingSpace(back.substr(1, back.size() - 2));
    } else {        //rel_expr
        left = "";
        right = StringFormatter::removeTrailingSpace(sourceCode);
        oper = "";
    }

    v.push_back(oper); // 0
    v.push_back(left); // 1
    v.push_back(right); // 2
}

void SourceTokenizer::extractRelExpr(string sourceCode, vector<string> &v) {
    int operPos = -1;
    int operLength = 2;
    operPos = sourceCode.find(">=");
    if (operPos == -1 || operPos == string::npos) {
        operPos = sourceCode.find("<=");
    }
    if (operPos == -1 || operPos == string::npos) {
        operPos = sourceCode.find("==");
    }
    if (operPos == -1 || operPos == string::npos) {
        operPos = sourceCode.find("!=");
    }
    if (operPos == -1 || operPos == string::npos) {
        operPos = sourceCode.find("<");
        operLength = 1;
    }
    if (operPos == -1 || operPos == string::npos) {
        operPos = sourceCode.find(">");
        operLength = 1;
    }
    if (operPos == -1 || operPos == string::npos) {
        throw "Relative operator not found";
    }

    string left = StringFormatter::removeTrailingSpace(sourceCode.substr(0,operPos));
    string right = StringFormatter::removeTrailingSpace(sourceCode.substr(operPos+operLength));
    string oper = sourceCode.substr(operPos, operLength);
    v.push_back(left);
    v.push_back(right);
    v.push_back(oper);
}

vector<string> SourceTokenizer::partitionAccordingToCase(std::string sourceCode, int type) {
    string trimmedCode;
    vector<string> v;
    switch(type) {
        case ASSIGN: case READ: case PRINT: case CALL: {
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
