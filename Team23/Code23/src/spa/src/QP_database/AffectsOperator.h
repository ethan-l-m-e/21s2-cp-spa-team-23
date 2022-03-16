//
// Created by Tin Hong Wen on 16/3/22.
//

#ifndef SPA_AFFECTSOPERATOR_H
#define SPA_AFFECTSOPERATOR_H


#include "CFGOperator.h"

class AffectsOperator: protected CFGOperator {
private:
    AffectsOperator();
protected:
    static AffectsOperator* singleton;
public:
    bool pathExistBetween(NodeCFG* left, NodeCFG* right, int CFGSize) override;
    //unordered_set<int> gatherAllLeftNodes(NodeCFG* rightNode, int CFGSize) override;
    //unordered_set<int> gatherAllRightNodes(NodeCFG* leftNode, int CFGSize) override;
    AffectsOperator *getInstance();

    bool IsReachableForward(NodeCFG *srcNode, NodeCFG *destNode, string variable, unordered_map<int, bool> &visited, vector<int> &path);
};


#endif //SPA_AFFECTSOPERATOR_H
