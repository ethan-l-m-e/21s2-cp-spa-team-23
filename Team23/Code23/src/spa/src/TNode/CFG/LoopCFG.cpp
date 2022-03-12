//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"
#include <vector>

LoopCFG::LoopCFG(int statementNumber): NodeCFG(statementNumber) {}

void LoopCFG::setNodeInLoop(NodeCFG *node) {
    this->nodeInLoop = node;
    node->addPreviousNode(this);
}

bool LoopCFG::isStart() {
    if(this->getAllPreviousNode().size() == 1) {
        unordered_map<int, NodeCFG*>::iterator i;
        i = this->getAllPreviousNode().begin();
        if(i->first > this->getStatementNumber()) { // previous node stmtNo is more than current
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
NodeCFG* LoopCFG::getNodeInLoop() {return this->nodeInLoop; }
