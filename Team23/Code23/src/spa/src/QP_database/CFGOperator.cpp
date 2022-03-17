//
// Created by Tin Hong Wen on 10/3/22.
//

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
    return DFSBoolean_func(left, right, CFGSize, IsReachableForward);
}

unordered_set<string> CFGOperator::gatherAllRightNodes(NodeCFG* leftNode, int CFGSize) {
    unordered_set<int> resultSet =  DFSResultSet_func(leftNode, CFGSize,collateAllAdjacentNodes,
                             searchNodesAlongPathAfter);
    return convertIntToString(resultSet);
}

unordered_set<string> CFGOperator::gatherAllLeftNodes(NodeCFG* rightNode, int CFGSize) {
    unordered_set<int> resultSet =   DFSResultSet_func(rightNode, CFGSize,collateAllPreviousNodes,
                             searchNodesAlongPathBefore);
    return convertIntToString(resultSet);
}


bool CFGOperator::IsReachableForward(NodeCFG* srcNode, NodeCFG* destNode,
                        unordered_map<int, bool> &visited,
                        vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    if(srcVal == destVal) {
        return true;
    }
    visited[srcVal] = true;
    path.push_back(srcVal);

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


bool CFGOperator::DFSBoolean_func(NodeCFG* left, NodeCFG* right, int CFGSize,
                                  bool(*dfsRecursionFoo)(NodeCFG* srcNode, NodeCFG* destNode,
                                                         unordered_map<int, bool> &visited,
                                                         vector<int> &path)){
    vector<int> path;
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    if (dfsRecursionFoo(left, right, visited, path)) {
        return true;
    } else {
        return false;
    }
}

unordered_set<int> CFGOperator::DFSResultSet_func(NodeCFG* currentNode, int CFGSize,
                                                  unordered_set<NodeCFG*>(*getAdjFoo)(NodeCFG*),
                                                  unordered_set<int>(*dfsRecursionFoo)(NodeCFG*, unordered_map<int, bool>&, unordered_set<int>)) {
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    unordered_set<NodeCFG *> adjNode = getAdjFoo(currentNode);
    unordered_set<int> resultNodes;
    for (NodeCFG *node: adjNode) {
        unordered_set<int> newSet = dfsRecursionFoo(node, visited, resultNodes);
        resultNodes.insert(newSet.begin(), newSet.end());
    }
    return resultNodes;
}


unordered_set<int> CFGOperator::DFSResultSetRecursion_func(NodeCFG* currentNode,
                                                           unordered_map<int, bool> &visited,
                                                           unordered_set<int> resultSet,
                                                           unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *)) {
    int currVal = currentNode->getStatementNumber();
    visited[currVal] = true;
    resultSet.insert(currVal);
    unordered_set<NodeCFG *> adjNodes = getAdjFoo(currentNode);
    unordered_set<NodeCFG *>::iterator adj;
    for (adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        if (!visited[adjacentNode->getStatementNumber()]) {
            unordered_set<int> resultSetInAdjacentNode = DFSResultSetRecursion_func(adjacentNode, visited, resultSet,
                                                                                    getAdjFoo);
            resultSet.insert(resultSetInAdjacentNode.begin(), resultSetInAdjacentNode.end());
        }
    }
    return resultSet;
}

unordered_set<int> CFGOperator::searchNodesAlongPathAfter(NodeCFG* leftNode,
                                             unordered_map<int, bool> &visited,
                                             unordered_set<int> nextSet) {
    return DFSResultSetRecursion_func(leftNode, visited, nextSet, collateAllAdjacentNodes);
}

unordered_set<int> CFGOperator::searchNodesAlongPathBefore(NodeCFG* rightNode,
                                              unordered_map<int, bool> &visited,
                                              unordered_set<int> nextSet) {
    return DFSResultSetRecursion_func(rightNode, visited, nextSet, collateAllPreviousNodes);
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

unordered_set<string> CFGOperator::convertIntToString(unordered_set<int> intSet) {
    unordered_set<string> stringSet = {};
    unordered_set<int>::iterator i;
    for(i = intSet.begin(); i!= intSet.end(); ++i) {
        stringSet.insert(to_string(*i));
    }
    return stringSet;
}