//
// Created by Tin Hong Wen on 10/3/22.
//
#pragma once

#ifndef SPA_GRAPHMETHODS_H
#define SPA_GRAPHMETHODS_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

#include "TNode/CFG/NodeCFG.h"

using namespace std;

class GraphMethods {
private:
    static GraphMethods* singleton;
    GraphMethods();
public:
    static bool IsReachableForward(NodeCFG* srcNode,
                                   NodeCFG* destNode,
                                   unordered_map<int, bool> &visited,
                                   vector<int> &path
                                   );


    static string printPath(vector<int> path);
    static unordered_set<NodeCFG*> collateAllAdjacentNodes(NodeCFG* node);
    static unordered_set<NodeCFG*> collateAllPreviousNodes(NodeCFG* node);
    static unordered_map<int, bool> constructVisitMap(int size);

    static bool DFSBoolean(NodeCFG *left, NodeCFG *right, int CFGSize,
                           bool (*dfsRecursionFoo)(NodeCFG *, NodeCFG *, unordered_map<int, bool> &, vector<int> &));

    static GraphMethods *getInstance();


};


#endif //SPA_GRAPHMETHODS_H
