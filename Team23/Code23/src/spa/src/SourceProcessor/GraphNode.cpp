//
// Created by Lucas Tai on 18/3/22.
//

#include "GraphNode.h"
GraphNode::GraphNode(string name, vector<ProcName> toOtherNodes) {
    this-> name = name;
    this->toOtherNodes = toOtherNodes;
}
vector<ProcName> GraphNode::getDirectedNodes() {
    return this->toOtherNodes;
}
string GraphNode::getName() {
    return this->name;
}
void GraphNode::changeName(string name) {
    this->name = name;
}