//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"
#include <vector>

LoopCFG::LoopCFG(int statementNumber): NodeCFG(statementNumber) {}

void LoopCFG::setNodeInLoop(NodeCFG *node) {this->nodeInLoop = node; }

NodeCFG* LoopCFG::getNodeInLoop() {return this->nodeInLoop; }
