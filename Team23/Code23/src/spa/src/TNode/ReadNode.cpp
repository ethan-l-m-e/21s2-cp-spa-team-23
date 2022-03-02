//
// Created by リム・イーサン on 2/3/22.
//

#include "ReadNode.h"

ReadNode::ReadNode(int num, VariableNode *varNode): StmtNode(num) {
    this->varNode = varNode;
    this->varNode->setParentNode(this);
}

VarName ReadNode::getVarName() const {
    return this->varNode->getVariableName();
}

vector<VarName> ReadNode::getListOfVarModified() {
    return vector<VarName>{this->getVarName()};
}
