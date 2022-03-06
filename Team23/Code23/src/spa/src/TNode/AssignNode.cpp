//
// Created by リム・イーサン on 2/3/22.
//

#include "AssignNode.h"

AssignNode::AssignNode(int num, VariableNode *leftNode, Expression rightNode) : StmtNode(num) {
    this ->leftNode = leftNode;
    this ->rightNode = rightNode;
    this ->leftNode ->setParentNode(this);
    visit([this](auto& n){n->setParentNode(this);},this->rightNode);
}

vector<VarName> AssignNode::getListOfVarUsed(){
    return BinaryOperatorNode::getAllVarFnHelper(this->getRightNode());
}
vector<VarName> AssignNode::getListOfVarModified(){
    vector<string> v = BinaryOperatorNode::getAllVarFnHelper(this->getLeftNode());
    return v;
}

vector<VarName> AssignNode::getAllVariables() {
    vector<VarName> vector1 = BinaryOperatorNode::getAllVarFnHelper(this->leftNode);
    vector<VarName> vector2 = BinaryOperatorNode::getAllVarFnHelper(this->rightNode);
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}

vector<Constant> AssignNode::getAllConstants() {
    return BinaryOperatorNode::getAllConstantHelper(this->getRightNode());
}

VariableNode* AssignNode::getLeftNode() const {
    return this ->leftNode;
}
Expression AssignNode::getRightNode() const {
    return this ->rightNode;
}
