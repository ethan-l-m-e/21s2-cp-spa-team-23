//
// Created by Tin Hong Wen on 6/2/22.
//
#include <vector>
#include <string>

#ifndef SPA_SOURCETOKENISER_H
#define SPA_SOURCETOKENISER_H

using namespace std;

class SourceTokenizer {
public:
    static void extractAssign(string, vector<string>&);
    static void extractIfElseThen(string, vector<string>&);
    static void extractWhile(string, vector<string>&);
    static string extractUntilParenthesesClosure(string, string);

    static void extractProcedure(string sourceCode, vector<string> &v);

    void extractExpression(string sourceCode, vector<string> &v);
};


#endif //SPA_SOURCETOKENISER_H
