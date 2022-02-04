//
// Created by Tin Hong Wen on 2/2/22.
//
#include <string>

#ifndef SPA_IDENTIFIER_H
#define SPA_IDENTIFIER_H

using namespace std;


class Identifier {
    public:
        int identifyFirstObject(string);
        void splitStringByLine(string, vector<string>&);
        vector<bool> checkSourceCodeStmt(string);
};


#endif //SPA_IDENTIFIER_H
