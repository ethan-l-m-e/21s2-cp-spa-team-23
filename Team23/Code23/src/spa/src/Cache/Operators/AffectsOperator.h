//
// Created by Tin Hong Wen on 16/3/22.
//

#ifndef SPA_AFFECTSOPERATOR_H
#define SPA_AFFECTSOPERATOR_H


#include "CacheOperator.h"

class AffectsOperator: protected CacheOperator {
public:
    bool computeRelation(string left, string right) override;
    stmtSetStr computeLHS(string right) override;
    stmtSetStr computeRHS(string left) override;
    static AffectsOperator *getInstance();

protected:
    AffectsOperator();
    static AffectsOperator* singleton;
    static bool isAssignStmt(string stmtNo);

    void setBlacklist(unordered_set<string> newSet);
    void setWhiteList(unordered_set<string> newSet);

    static bool isInBlackList(int stmtNo);
    static bool isInWhiteList(int stmtNo);

    variableSet getVarModifiedBy(string stmt);
    variableSet getVarUsedBy(string stmt);

    bool isContainerStatement(string stmtNo);

    stmtSetStr removeContainerFromSet(unordered_set<string> &stmtSet);

    static bool IsReachableForward(NodeCFG *srcNode, NodeCFG *destNode, unordered_map<int, bool> &visited, vector<int> &path);
};


#endif //SPA_AFFECTSOPERATOR_H
