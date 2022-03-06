//
// Created by リム・イーサン on 2/3/22.
//

#include "RelExprNode.h"

RelExprNode::RelExprNode(RelFactor leftNode, RelFactor rightNode, string relativeOperator) {
    this->leftNode = leftNode;
    visit([this](auto n){n->setParentNode(this);}, this->leftNode);
    this->rightNode = rightNode;
    visit([this](auto n){n->setParentNode(this);}, this->rightNode);
    this->relativeOperator = std::move(relativeOperator);
}

RelFactor RelExprNode::getLeftFactor() const {
    return this->leftNode;
}

RelFactor RelExprNode::getRightFactor() const {
    return this->rightNode;
}

string RelExprNode::getRelativeOperator() const {
    return this->relativeOperator;
}

vector<VarName> RelExprNode::getAllVariables() {
    vector<VarName> vector1 = BinaryOperatorNode::getAllVarFnHelper(this->leftNode);
    vector<VarName> vector2 = BinaryOperatorNode::getAllVarFnHelper(this->rightNode);
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}

vector<Constant> RelExprNode::getAllConstants() {
    vector<Constant> vector1 = BinaryOperatorNode::getAllConstantHelper(this->leftNode);
    vector<Constant> vector2 = BinaryOperatorNode::getAllConstantHelper(this->rightNode);
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}
