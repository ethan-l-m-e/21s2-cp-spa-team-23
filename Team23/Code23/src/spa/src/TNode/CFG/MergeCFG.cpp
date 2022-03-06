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


