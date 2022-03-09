//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"

MergeCFG::MergeCFG(int statementNumber): NodeCFG(statementNumber) {

}

void MergeCFG::setLeftPreviousNode(NodeCFG *node) {
    this->leftPreviousNode = node;
    this->previousNode = this->leftPreviousNode;
}

void MergeCFG::setRightPreviousNode(NodeCFG *node) {this->rightPreviousNode = node;}

NodeCFG* MergeCFG::getLeftPreviousNode() { return this->leftPreviousNode;}

NodeCFG* MergeCFG::getRightPreviousNode() { return this->rightPreviousNode;}

NodeCFG* ImagineMergeCFG::getEndNode() {
    if(this->getLeftPreviousNode()->getStatementNumber() > this->getRightPreviousNode()->getStatementNumber())
        return this->getLeftPreviousNode();
    else if(this->getLeftPreviousNode()->getStatementNumber() < this->getRightPreviousNode()->getStatementNumber())
        return this->getRightPreviousNode();
    else
        throw "both left and right previous nodes of imaginaryMergeNode cannot be the same node! leftNode: " +
                to_string(this->getLeftPreviousNode()->getStatementNumber()) +
                "rightNode: " + to_string(this->getRightPreviousNode()->getStatementNumber());
}
