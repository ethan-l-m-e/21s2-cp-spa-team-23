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
            return true;
        }
        else {
            unordered_map<int, NodeCFG*>::iterator i;
            for(i = this->getAllPreviousNode().begin(); i != this->getAllPreviousNode().end(); ++i){
                if(i->first < this->getStatementNumber()) {
                    return true;
                }
            }
            return false;
        }
}
NodeCFG* LoopCFG::getNodeInLoop() {return this->nodeInLoop; }
