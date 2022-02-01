//
// Created by Tin Hong Wen on 28/1/22.
//

#include "TNode.h"

TNode::TNode(string name) {
    this -> value = name;
}

void TNode::addNode(TNode &nodeRef) {
    // add node ref into the childrenRef
    childrenRef.push_back(nodeRef);
}

void TNode::removeNode(int index) {
    childrenRef.erase(childrenRef.begin() + (index - 1));
}

TNode TNode::getNode(int index) {
    return childrenRef[index];
}

string TNode::getValue() {
    return value;
}

void TNode::changeValue(string value) {
    this -> value = value;
}