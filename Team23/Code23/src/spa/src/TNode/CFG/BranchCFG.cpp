//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"

BranchCFG::BranchCFG(int statementNumber): NodeCFG(statementNumber) {
}

void BranchCFG::setLeftNode(NodeCFG *node) {
    this->leftNode = node;
}

void BranchCFG::setRightNode(NodeCFG *node) {
    this->rightNode = node;
    this->nextNode = this->rightNode;
}

NodeCFG* BranchCFG::getLeftNode() { return this->leftNode;}

NodeCFG* BranchCFG::getRightNode() { return this->rightNode;}

NodeCFG* BranchCFG::getLastLeftNode() { return this->getLeftNode()->getEndNode();}

NodeCFG* BranchCFG::getLastRightNode() { return this->getRightNode()->getEndNode();}
