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
    static bool IsReachableForward(NodeCFG* srcNode, NodeCFG* destNode, unordered_map<int, bool> &visited, vector<int> &path);
    static unordered_set<int> searchNodesAlongPathAfter(NodeCFG* leftNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
    static unordered_set<int> searchNodesAlongPathBefore(NodeCFG* rightNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
protected:
    static string printPath(vector<int> path);
    static unordered_set<NodeCFG*> collateAllAdjacentNodes(NodeCFG* node);
    static unordered_set<NodeCFG*> collateAllPreviousNodes(NodeCFG* node);
    static unordered_map<int, bool> constructVisitMap(int size);

public:
    static bool pathExistBetween(NodeCFG* left, NodeCFG* right, int CFGSize);
    static unordered_set<int> gatherAllLeftNodes(NodeCFG* rightNode, int CFGSize);
    static unordered_set<int> gatherAllRightNodes(NodeCFG* leftNode, int CFGSize);

    static CFGOperator *getInstance();
};


#endif //SPA_CFGOPERATOR_H
