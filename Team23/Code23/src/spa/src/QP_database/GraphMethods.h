//
// Created by Tin Hong Wen on 10/3/22.
//
#pragma once

#ifndef SPA_EXECUTIONPATHSERVICES_H
#define SPA_EXECUTIONPATHSERVICES_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

#include "TNode/CFG/NodeCFG.h"

using namespace std;

class ExecutionPathServices {
private:
    static ExecutionPathServices* singleton;
    ExecutionPathServices();
public:
    static bool IsReachableForward(NodeCFG* srcNode,
                                   NodeCFG* destNode,
                                   unordered_map<int, bool> &visited,
                                   vector<int> &path
                                   );

    static unordered_set<int> searchNodesAlongPathAfter(NodeCFG* leftNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
    static unordered_set<int> searchNodesAlongPathBefore(NodeCFG* rightNode, unordered_map<int, bool> &visited, unordered_set<int> nextSet);
    static string printPath(vector<int> path);
    static unordered_set<NodeCFG*> collateAllAdjacentNodes(NodeCFG* node);
    static unordered_set<NodeCFG*> collateAllPreviousNodes(NodeCFG* node);
    static unordered_map<int, bool> constructVisitMap(int size);

    static bool DFSBoolean(NodeCFG *left, NodeCFG *right, int CFGSize,
                           bool (*dfsRecursionFoo)(NodeCFG *, NodeCFG *, unordered_map<int, bool> &, vector<int> &));

    static unordered_set<int> DFSResultSet(NodeCFG *currentNode, int CFGSize, unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *),
                                           unordered_set<int> (*dfsRecursionFoo)(NodeCFG *, unordered_map<int, bool>&,
                                                                                          unordered_set<int>));
    static unordered_set<int> DFSResultSetRecursion(NodeCFG* currentNode,
                                                    unordered_map<int, bool> &visited,
                                                    unordered_set<int> resultSet, unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *));

    static ExecutionPathServices *getInstance();


};


#endif //SPA_EXECUTIONPATHSERVICES_H
