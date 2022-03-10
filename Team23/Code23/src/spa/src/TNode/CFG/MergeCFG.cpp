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





NodeCFG* getEndNodeAscendRight(ImagineMergeCFG* imgNode) {
    if(auto img = dynamic_cast<ImagineMergeCFG*>(imgNode->getRightPreviousNode())) {
        return getEndNodeAscendRight(img);
    } else {
        return imgNode->getRightPreviousNode();
    }
}
/*
 * Imaginary Merge can happen in these cases:
 * 1) last statement in the procedure is an if statement
 * 2) last statement in a while/if statement is an if statement
 *
 */
NodeCFG* ImagineMergeCFG::getEndNode() {
    if(this->nextNode == nullptr) {
        return getEndNodeAscendRight(this);
    } else {    // there is next node, but not sure if imaginary
        return this->nextNode->getEndNode();
    }

    /*
    if(this->nextNode != nullptr) {
        return this->nextNode->getEndNode();
    }

    else if (auto img2 = dynamic_cast<ImagineMergeCFG*>(this-> getRightPreviousNode())) {
        // means both left and right previous values are imaginary
        return img2->getEndNode();
    }
    else if(this->getLeftPreviousNode()->getStatementNumber() > this->getRightPreviousNode()->getStatementNumber())
        return this->getLeftPreviousNode();
    else if(this->getLeftPreviousNode()->getStatementNumber() < this->getRightPreviousNode()->getStatementNumber())
        return this->getRightPreviousNode();
     else
        throw "both left and right previous nodes of imaginaryMergeNode cannot be the same node! leftNode: " +
                to_string(this->getLeftPreviousNode()->getStatementNumber()) +
                "rightNode: " + to_string(this->getRightPreviousNode()->getStatementNumber());
    */

}
