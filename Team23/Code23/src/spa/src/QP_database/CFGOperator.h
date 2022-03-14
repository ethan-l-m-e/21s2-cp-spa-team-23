//
// Created by Tin Hong Wen on 10/3/22.
//

#ifndef SPA_CFGOPERATOR_H
#define SPA_CFGOPERATOR_H

#include <string>
#include <unordered_set>
#include <map>

#include "TNode/CFG/NodeCFG.h"

using namespace std;

class CFGOperator {
private:
    CFGOperator();
    static CFGOperator* singleton;

public:
    static bool pathExistBetween(NodeCFG* left, NodeCFG* right, int CFGSize);
    static unordered_set<int> gatherAllLeftNodesNext(NodeCFG* rightNode, int CFGSize);
    static unordered_set<int> gatherAllRightNodesNext(NodeCFG* leftNode, int CFGSize);

    static CFGOperator *getInstance();
};


#endif //SPA_CFGOPERATOR_H
