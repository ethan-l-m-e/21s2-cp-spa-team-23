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
}

void NodeCFG::addPreviousNode(NodeCFG* node) {
    this->mapOfPreviousNodes[node->getStatementNumber()] = node;
}

NodeCFG* NodeCFG::getNextNode() {
    return this->nextNode;
}
unordered_map<int, NodeCFG*> NodeCFG::getAllPreviousNode() {
    return this->mapOfPreviousNodes;
}

NodeCFG* NodeCFG::getStartNode() {
    if(this->mapOfPreviousNodes.size() == 0) {
        return this;
    } else {
        for(auto x : this->mapOfPreviousNodes) {
            return x.second->getStartNode();
        }
    }
}

 NodeCFG* NodeCFG::getEndNode() {
     if(this->nextNode== nullptr) {
         return this;
     } else {
         return this->nextNode->getEndNode();
     }
}

bool NodeCFG::isStart() {
    return this->mapOfPreviousNodes.size() == 0;
}

bool NodeCFG::isEnd() {
    return this->nextNode == nullptr;
}

