//
// Created by Tin Hong Wen on 10/3/22.
//

#include "GraphMethods.h"

using namespace std;


GraphMethods *GraphMethods::singleton = nullptr;
GraphMethods::GraphMethods() {}
GraphMethods* GraphMethods::getInstance() {
    if (GraphMethods::singleton == nullptr) {
        GraphMethods::singleton = new GraphMethods();
    }
    return GraphMethods::singleton;
}


// final checks algo
bool GraphMethods::IsReachableForward(NodeCFG* srcNode,
                                      NodeCFG* destNode,
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
        // if not visited, perform recursion again
        int adjStmtNo = adjacentNode->getStatementNumber();
        if (!visited[adjStmtNo] && IsReachableForward(adjacentNode, destNode, visited, path))
                return true;
    }
    path.pop_back();
    return false;
}

bool GraphMethods::DFSBoolean(NodeCFG* left, NodeCFG* right, int CFGSize,
                              bool(*dfsRecursionFoo)(NodeCFG* srcNode, NodeCFG* destNode,
                                                         unordered_map<int, bool> &visited,
                                                         vector<int> &path)){
    vector<int> path;
    unordered_map<int, bool> visited = constructVisitMap(CFGSize);
    unordered_set<NodeCFG*> adjNodes = collateAllAdjacentNodes(left);
    for(NodeCFG* node : adjNodes) {
        if (dfsRecursionFoo(node, right, visited, path)) return true;
    }
    return false;
}

unordered_set<NodeCFG*> GraphMethods::collateAllPreviousNodes(NodeCFG* node) {
    unordered_map<int, NodeCFG*> nodeMap = node->getAllPreviousNode();
    unordered_map<int, NodeCFG*>::iterator i;
    unordered_set<NodeCFG*> outputSet;
    for(i = nodeMap.begin(); i != nodeMap.end(); i++) {
        NodeCFG* node = (*i).second;
        outputSet.insert(node);
    }
    return outputSet;
}

unordered_set<NodeCFG*> GraphMethods::collateAllAdjacentNodes(NodeCFG* node) {
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

unordered_map<int, bool> GraphMethods::constructVisitMap(int size) {
    unordered_map<int, bool> v;
    for(int i = 1; i <= size; i++) {
        v[i] = false;
    }
    return v;
}

string GraphMethods::printPath(vector<int> path) {
    vector<int>::iterator i;
    string output = "";
    for(int i: path) {
        output = output + " " + to_string(i);
    }
    return output;
}