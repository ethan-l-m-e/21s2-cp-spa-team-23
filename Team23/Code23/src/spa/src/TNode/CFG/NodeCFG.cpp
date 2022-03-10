//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"

NodeCFG::NodeCFG(int statementNumber) {
    this->statementNumber = statementNumber;
    this->previousNode = nullptr;
    this->nextNode = nullptr;
}

int NodeCFG::getStatementNumber() {
    return this->statementNumber;
}

void NodeCFG::setNextNode(NodeCFG* node) {
    this->nextNode = node;
}

void NodeCFG::setPreviousNode(NodeCFG* node) {
    this->previousNode = node;
}

NodeCFG* NodeCFG::getNextNode() {
    return this->nextNode;
}
NodeCFG* NodeCFG::getPreviousNode() {
    return this->previousNode;
}

NodeCFG* NodeCFG::getStartNode() {
    if(this->previousNode== nullptr) {
        return this;
    } else {
        return this->previousNode->getStartNode();
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
    return this->previousNode == nullptr;
}

bool NodeCFG::isEnd() {
    return this->nextNode == nullptr;
}

