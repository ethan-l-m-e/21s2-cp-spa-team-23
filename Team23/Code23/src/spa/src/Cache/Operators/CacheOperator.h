//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_CACHEOPERATOR_H
#define SPA_CACHEOPERATOR_H

#include "GraphMethods.h"
#include "PKB/PKB.h"
//#include "Cache/Cache.h"

class CacheOperator {
    /*
     * Operator class is to compute results (in-computation instead of pre-computation)
     */
public:
    virtual bool computeRelation(string left, string right);
    virtual unordered_set<string> computeLHS(string rightNode);
    virtual unordered_set<string> computeRHS(string leftNode);

    bool isOptimised();

    CacheOperator* setOptimisation(bool in);
    bool stmtIsNotInSource(vector<string> argList);

    NodeCFG* retrieveNode(string stmtNo);
    int getSize();
    unordered_set<string> convertIntToString(unordered_set<int> intSet);

protected:
    typedef unordered_set<string> variableSet, stmtSetStr;
    typedef unordered_set<int> stmtSetNum;
    typedef  string stmtStr, variable;
    typedef  int statementNum;

    static PKB* pkb;
    static GraphMethods* graphMethods;
};


#endif //SPA_CACHEOPERATOR_H
