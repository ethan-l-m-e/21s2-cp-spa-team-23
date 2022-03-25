//
// Created by Tin Hong Wen on 4/3/22.
//

#include "NodeCFG.h"
#include <vector>
#include <unordered_set>
#include <iostream>
LoopCFG::LoopCFG(int statementNumber): NodeCFG(statementNumber) {}

void LoopCFG::setNodeInLoop(NodeCFG *node) {

        this->nodeInLoop = node;
        node->addPreviousNode(this);
}

bool LoopCFG::isStart() {
    auto allPrevNode = this->getAllPreviousNode();
    unordered_map<int, NodeCFG*>::iterator i;
    for(i = allPrevNode.begin(); i != allPrevNode.end(); i++) {
        if(i->first < this->getStatementNumber()) {
            return false;
        }
    }
    return true;

}
NodeCFG* LoopCFG::getNodeInLoop() {return this->nodeInLoop; }

vector<int> LoopCFG::generateNodesInLoopList() {
    auto allPrevNode = this->getAllPreviousNode();
    int currentNum = this->getStatementNumber();
    int previousInLoop = currentNum;
    unordered_map<int, NodeCFG*>::iterator i;
    for(i = allPrevNode.begin(); i != allPrevNode.end(); i++) {
        if(i->first > previousInLoop) {
            previousInLoop = i->first;
        }
    }

    //generate a list quickly
    std::vector<int> v(previousInLoop - currentNum);
    std::generate(v.begin(), v.end(), [n = currentNum + 1] () mutable { return n++; });
    return v;
}