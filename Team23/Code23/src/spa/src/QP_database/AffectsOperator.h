//
// Created by Tin Hong Wen on 16/3/22.
//

#ifndef SPA_AFFECTSOPERATOR_H
#define SPA_AFFECTSOPERATOR_H


#include "CacheOperator.h"

class AffectsOperator: protected CacheOperator {
public:
    AffectsOperator(PKB *pkb);

    bool findRelation(string left, string right) override;
    stmtSetStr findLHS(string right) override;
    stmtSetStr findRHS(string left) override;
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
    static stmtSetStr getStmtModifying(string var);
    static stmtSetStr getStmtUsing(string var);

    bool isContainerStatement(string stmtNo);

    stmtSetStr removeContainerFromSet(unordered_set<string> &stmtSet);

    stmtSetNum
    static DFSResultSetRecursion(NodeCFG *currentNode, unordered_map<int, bool> &visited, unordered_set<int> resultSet,
                          unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *));

    stmtSetNum
    static searchForAffectsBefore(NodeCFG *rightNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);

    stmtSetNum
    static searchForAffectsAfter(NodeCFG *leftNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);

    static bool IsReachableForward(NodeCFG *srcNode, NodeCFG *destNode, unordered_map<int, bool> &visited, vector<int> &path);

    stmtSetStr
    findResultSet(string stmt,
                  variableSet variables,
                  pair<stmtSetStr, stmtSetStr >(*blackAndWhiteListFoo)(string),
                  unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *),
                  stmtSetNum (*dfsRecursionFoo)(NodeCFG *, unordered_map<int, bool> &, unordered_set<int>));

};


#endif //SPA_AFFECTSOPERATOR_H
