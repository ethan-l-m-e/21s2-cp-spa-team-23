//
// Created by Tin Hong Wen on 28/1/22.
//
#include <iostream>
#include "TNode.h"

using namespace std;

TNode::TNode(string name) {
    this -> value = name;
}

TNode::TNode(string name, int stmtNo) {
    this -> value = name;
    this -> stmtNo = stmtNo;
}

void TNode::addNode(TNode *nodeRef) {
    // add node ref into the childrenRef
    childrenRef.push_back(nodeRef);
}

void TNode::removeNode(int index) {
    childrenRef.erase(childrenRef.begin() + (index - 1));
}

TNode *TNode::getNode(int index) {
    return childrenRef[index];
}

int TNode::getNumberOfChildNodes() {
    return childrenRef.size();
}

string TNode::getValue() {
    return value;
}

void TNode::changeValue(string value) {
    this -> value = value;
}

bool TNode::hasStmtNo() {
    if (this -> stmtNo > 0)
        return true;
    else
        return false;
}

int TNode::getStmtNo() {
    return stmtNo;
}

void TNode::setStmtNo(int stmtNo) {
    this -> stmtNo = stmtNo;
}