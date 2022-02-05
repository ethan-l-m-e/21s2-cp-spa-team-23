//
// Created by Lucas Tai on 3/2/22.
//

#include "Extractor.h"

std::string* information;

Extractor* Extractor::extractAssign(std::string sourceCode) {

    std::string assignInfo[2];

    sourceCode.erase(std::remove_if(sourceCode.begin(),sourceCode.end(), isspace),sourceCode.end());
    int pos = sourceCode.find('=');
    std::string varName;
    for (int i = 0; i<pos;i++) {
        varName.push_back(sourceCode[i]);
    }
    assignInfo[0] = varName;
    std::string expr;
    for (int i = pos; i<sourceCode.length();i++) {
        expr.push_back(sourceCode[i]);
    }
    assignInfo[1] = expr;
    information = assignInfo;
    return this;
}

std::string Extractor::getAssignVar(){
    return information[0];
}

std::string Extractor::getAssignExpr(){
    return information[1];
}

Extractor* Extractor::extractProcedure(std::string sourceCode) {
    std::string procInfo[2];
    sourceCode.erase(std::remove_if(sourceCode.begin(),sourceCode.end(), isspace),sourceCode.end());
    int procedurePos = sourceCode.find("procedure");
    sourceCode = sourceCode.substr(procedurePos+9,sourceCode.size());
    int pos = sourceCode.find('{');
    std::string procName;
    for (int i = 0; i<pos;i++) {
        procName.push_back(sourceCode[i]);
    }
    procInfo[0] = procName;
    std::string stmtLst;
    for (int i = pos; i<sourceCode.length();i++) {
        stmtLst.push_back(sourceCode[i]);
    }
    procInfo[1] = stmtLst;
    information = procInfo;
    return this;
}

std::string Extractor::getProcName(){
    return information[0];
}

std::string Extractor::getProcStmtLst(){
    return information[1];
}

Extractor* Extractor::extractExpression(std::string sourceCode) {
//    std::string exprInfo[3];
//    std::string init = sourceCode;
//    int bracketFlag = 0;
//    for (int i = sourceCode.length();i>=0;i--){
//        switch(sourceCode[i]) {
//            case ')':
//                bracketFlag = 1;
//                break;
//            case '+':
//                break;
//            case '-':
//                break;
//            case '*':
//                break;
//            case '/':
//                break;
//            case '(':
//                break;
//        }
//
//
//    }

    return this;
}