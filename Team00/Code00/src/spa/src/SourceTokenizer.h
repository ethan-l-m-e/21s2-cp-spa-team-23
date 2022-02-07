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
    static string extractUntilParenthesesClosure(string, string);
};


#endif //SPA_SOURCETOKENISER_H
