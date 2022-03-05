//
// Created by Tin Hong Wen on 6/2/22.
//
#include <vector>
#include <string>
#include "Constants/Constants.h"
#ifndef SPA_SOURCETOKENISER_H
#define SPA_SOURCETOKENISER_H

using namespace std;

class SourceTokenizer {
public:
    static vector<string> partitionAccordingToCase(std::string sourceCode, int type);

    static void extractCall(string, vector<string>&);
    static void extractRead(string, vector<string>&);
    static void extractPrint(string, vector<string>&);
    static void extractAssign(string, vector<string>&);
    static void extractIfElseThen(string, vector<string>&);
    static void extractWhile(string, vector<string>&);
    static string extractUntilParenthesesClosure(string, string);

    static void extractProcedure(string sourceCode, vector<string> &v);
    static void extractCondExpr(string sourceCode, vector<string> &v);
    static void extractExpression(string sourceCode, vector<string> &v);
    static void extractRelExpr(string sourceCode, vector<string> &v);
};


#endif //SPA_SOURCETOKENISER_H
