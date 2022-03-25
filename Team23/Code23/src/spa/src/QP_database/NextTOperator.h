//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_NEXTTOPERATOR_H
#define SPA_NEXTTOPERATOR_H

#include "CacheOperator.h"

class NextTOperator : protected CacheOperator {
public:
    bool computeRelation(string left, string right) override;
    stmtSetStr computeLHS(string rightNode) override;
    stmtSetStr computeRHS(string leftNode) override;
    static NextTOperator *getInstance();

protected:
    NextTOperator();
    static NextTOperator* singleton;

    unordered_set<int>
    searchNodesAlongPathAfter(NodeCFG *leftNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);

    static bool IsReachableForward(NodeCFG *srcNode, NodeCFG *destNode, unordered_map<int, bool> &visited, vector<int> &path);
};


#endif //SPA_NEXTTOPERATOR_H
