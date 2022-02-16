//
// Created by Tin Hong Wen on 2/2/22.
//
#include <string>

#ifndef SPA_IDENTIFIER_H
#define SPA_IDENTIFIER_H

using namespace std;

class Identifier {
    public:
        static int identifyFirstObject(string);
        static bool checkParenthesesClosure(string code, string brackets);
};
#endif //SPA_IDENTIFIER_H
