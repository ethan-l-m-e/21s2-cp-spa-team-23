//
// Created by Tin Hong Wen on 10/3/22.
//
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "CFGOperator.h"

using namespace std;



CFGOperator *CFGOperator::singleton = nullptr;

CFGOperator::CFGOperator() {}
CFGOperator* CFGOperator::getInstance() {
    if (CFGOperator::singleton == nullptr) {
        CFGOperator::singleton = new CFGOperator();
    }
    return CFGOperator::singleton;
}

bool CFGOperator::pathExistBetween(NodeCFG* left, NodeCFG* right, int CFGSize) {
    vector<int> path;
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    if (IsReachableForward(left, right, visited, path)) {
        return true;
    } else {
        return false;
    }
}

/*
 * planning for affects:
 * same thing as nextTClauseEvaluator
 *
 *
 *
 *
 */


unordered_set<int> CFGOperator::gatherAllRightNodes(NodeCFG* leftNode, int CFGSize) {
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    unordered_set<NodeCFG*> adjNode = collateAllAdjacentNodes(leftNode);
    unordered_set<int> allNodesAfter;
    for(NodeCFG* node: adjNode) {
        unordered_set<int> newSet = searchNodesAlongPathAfter(node, visited, allNodesAfter);
        allNodesAfter.insert(newSet.begin(), newSet.end());
    }
    return allNodesAfter;
}

unordered_set<int> CFGOperator::gatherAllLeftNodes(NodeCFG* rightNode, int CFGSize) {
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    unordered_set<NodeCFG*> adjNode = collateAllPreviousNodes(rightNode);
    unordered_set<int> allNodesBefore;
    for(NodeCFG* node: adjNode) {
        unordered_set<int> newSet = searchNodesAlongPathBefore(node, visited, allNodesBefore);
        allNodesBefore.insert(newSet.begin(), newSet.end());
    }
    return allNodesBefore;
}

bool CFGOperator::IsReachableForward(NodeCFG* srcNode, NodeCFG* destNode,
                        unordered_map<int, bool> &visited,
                        vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    visited[srcVal] = true;
    path.push_back(srcVal);

    if(srcVal == destVal) {
        return true;
    }
    unordered_set<NodeCFG*> adjNodes = collateAllAdjacentNodes(srcNode);
    unordered_set<NodeCFG*>::iterator adj;
    for(adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        if (!visited[adjacentNode->getStatementNumber()]) {
            if (IsReachableForward(adjacentNode, destNode, visited, path))
                return true;
        }
    }
    path.pop_back();
    return false;
}


unordered_set<int> CFGOperator::searchNodesAlongPathAfter(NodeCFG* leftNode,
                                             unordered_map<int, bool> &visited,
                                             unordered_set<int> nextSet) {
    int currVal = leftNode->getStatementNumber();
    visited[currVal] = true;
    nextSet.insert(currVal);
    unordered_set<NodeCFG*> adjNodes = collateAllAdjacentNodes(leftNode);
    unordered_set<NodeCFG*>::iterator adj;
    for(adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        if (!visited[adjacentNode->getStatementNumber()]) {
            unordered_set<int> nextSetInAdj = searchNodesAlongPathAfter(adjacentNode, visited, nextSet);
            nextSet.insert(nextSetInAdj.begin(), nextSetInAdj.end());
        }
    }
    return nextSet;
}

unordered_set<int> CFGOperator::searchNodesAlongPathBefore(NodeCFG* rightNode,
                                              unordered_map<int, bool> &visited,
                                              unordered_set<int> nextSet) {
    int currVal = rightNode->getStatementNumber();
    visited[currVal] = true;
    nextSet.insert(currVal);
    unordered_set<NodeCFG*> adjNodes = collateAllPreviousNodes(rightNode);
    unordered_set<NodeCFG*>::iterator adj;
    for(adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        if (!visited[adjacentNode->getStatementNumber()]) {
            unordered_set<int> nextSetInAdj = searchNodesAlongPathBefore(adjacentNode, visited, nextSet);
            nextSet.insert(nextSetInAdj.begin(), nextSetInAdj.end());
        }
    }
    return nextSet;
}


unordered_set<NodeCFG*> CFGOperator::collateAllPreviousNodes(NodeCFG* node) {
    unordered_map<int, NodeCFG*> nodeMap = node->getAllPreviousNode();
    unordered_map<int, NodeCFG*>::iterator i;
    unordered_set<NodeCFG*> outputSet;
    for(i = nodeMap.begin(); i != nodeMap.end(); i++) {
        NodeCFG* node = (*i).second;
        outputSet.insert(node);
    }
    return outputSet;
}

unordered_set<NodeCFG*> CFGOperator::collateAllAdjacentNodes(NodeCFG* node) {
    unordered_set<NodeCFG*> adjNodes;
    if(auto branch = dynamic_cast<BranchCFG*>(node)) {
        adjNodes.insert(branch->getLeftNode());
        adjNodes.insert(branch->getRightNode());
    }
    if (auto loop = dynamic_cast<LoopCFG*>(node)) {
        adjNodes.insert(loop->getNodeInLoop());
    }
    if(!node->isEnd()) {
        adjNodes.insert(node->getNextNode());
    }
    return adjNodes;
}


unordered_map<int, bool> CFGOperator::constructVisitMap(int size) {
    unordered_map<int, bool> v;
    for(int i = 1; i <= size; i++) {
        v[i] = false;
    }
    return v;
}

string CFGOperator::printPath(vector<int> path) {
    vector<int>::iterator i;
    string output = "";
    for(int i: path) {
        output = output + " " + to_string(i);
    }
    return output;
}