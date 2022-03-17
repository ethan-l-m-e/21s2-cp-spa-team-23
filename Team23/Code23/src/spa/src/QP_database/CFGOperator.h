//
// Created by Tin Hong Wen on 10/3/22.
//
#pragma once

#ifndef SPA_CFGOPERATOR_H
#define SPA_CFGOPERATOR_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

#include "TNode/CFG/NodeCFG.h"

using namespace std;

class CFGOperator {
private:
    static CFGOperator* singleton;
    CFGOperator();
    static bool IsReachableForward(NodeCFG* srcNode, NodeCFG* destNode, unordered_map<int, bool> &visited, vector<int> &path);
    static unordered_set<int> searchNodesAlongPathAfter(NodeCFG* leftNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
    static unordered_set<int> searchNodesAlongPathBefore(NodeCFG* rightNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
protected:
    static string printPath(vector<int> path);
    static unordered_set<NodeCFG*> collateAllAdjacentNodes(NodeCFG* node);
    static unordered_set<NodeCFG*> collateAllPreviousNodes(NodeCFG* node);
    static unordered_map<int, bool> constructVisitMap(int size);
    static unordered_set<string> convertIntToString(unordered_set<int> intSet);

    static bool DFSBoolean_func(NodeCFG *left, NodeCFG *right, int CFGSize,
                         bool (*dfsRecursionFoo)(NodeCFG *, NodeCFG *, unordered_map<int, bool> &, vector<int> &));

    static unordered_set<int> DFSResultSet_func(NodeCFG *currentNode, int CFGSize, unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *),
                                                unordered_set<int> (*dfsRecursionFoo)(NodeCFG *, unordered_map<int, bool>&,
                                                                                          unordered_set<int>));
    static unordered_set<int> DFSResultSetRecursion_func(NodeCFG* currentNode,
                                                         unordered_map<int, bool> &visited,
                                                         unordered_set<int> resultSet, unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *));
public:
    static CFGOperator *getInstance();
    virtual bool pathExistBetween(NodeCFG* left, NodeCFG* right, int CFGSize);
    virtual unordered_set<string> gatherAllLeftNodes(NodeCFG* rightNode, int CFGSize);
    virtual unordered_set<string> gatherAllRightNodes(NodeCFG* leftNode, int CFGSize);
};


#endif //SPA_CFGOPERATOR_H
