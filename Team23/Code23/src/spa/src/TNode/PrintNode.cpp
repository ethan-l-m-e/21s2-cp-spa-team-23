//
// Created by リム・イーサン on 2/3/22.
//

#include "PrintNode.h"

PrintNode::PrintNode(int num, VariableNode *varNode): StmtNode(num) {
    this->varNode = varNode;
    this->varNode->setParentNode(this);
}

VarName PrintNode::getVarName() const {
    return this->varNode->getVariableName();
}

vector<VarName> PrintNode::getListOfVarUsed() {
    return vector<VarName>{this->getVarName()};
}
