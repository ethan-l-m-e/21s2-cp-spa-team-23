//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"

NodeCFG::NodeCFG(int statementNumber) {
    this->statementNumber = statementNumber;
    this->mapOfPreviousNodes = unordered_map<int, NodeCFG*>{};
    this->nextNode = nullptr;
}

int NodeCFG::getStatementNumber() {
    return this->statementNumber;
}

void NodeCFG::setNextNode(NodeCFG* node) {
    this->nextNode = node;
    node->addPreviousNode(this);
}

void NodeCFG::addPreviousNode(NodeCFG* node) {
    this->mapOfPreviousNodes[node->getStatementNumber()] = node;
}

void NodeCFG::setAllPreviousNodes(unordered_map<int, NodeCFG*> allPrevNodesMap) {
    for (pair<const int, NodeCFG *> s: allPrevNodesMap) {
        this->mapOfPreviousNodes.insert(s);
    }
}

NodeCFG* NodeCFG::getNextNode() {
    return this->nextNode;
}
unordered_map<int, NodeCFG*> NodeCFG::getAllPreviousNode() {
    return this->mapOfPreviousNodes;
}

bool NodeCFG::isStart() {
    return this->mapOfPreviousNodes.size() == 0;
}

bool NodeCFG::isEnd() {
    return this->nextNode == nullptr;
}

