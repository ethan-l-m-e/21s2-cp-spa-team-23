//
// Created by リム・イーサン on 2/3/22.
//

#include "BinaryOperatorNode.h"

BinaryOperatorNode::BinaryOperatorNode(Expression leftExpr, Expression rightExpr, string binaryOperator) {
    this->leftExpr = leftExpr;
    visit([this](auto& n){n->setParentNode(this);},this->leftExpr);
    this->rightExpr = rightExpr;
    visit([this](auto& n){n->setParentNode(this);},this->rightExpr);
    this->binaryOperator = std::move(binaryOperator);
}

Expression BinaryOperatorNode::getLeftExpr() const {
    return this->leftExpr;
}

Expression BinaryOperatorNode::getRightExpr() const {
    return this->rightExpr;
}

string BinaryOperatorNode::getBinaryOperator() const {
    return this->binaryOperator;
}

vector<Constant> BinaryOperatorNode::getAllConstantHelper(Factor e) {
    vector<Constant> vec1;
    if(ConstValueNode** v = std::get_if<ConstValueNode*>(&e)){
        ConstValueNode constNode = **v;
        vec1.push_back(constNode.getConstValue());
    }else if (BinaryOperatorNode** b = std::get_if<BinaryOperatorNode*>(&e)){
        BinaryOperatorNode binNode = **b;
        vector<VarName> left = getAllConstantHelper(binNode.getLeftExpr());
        vec1.insert(vec1.begin(),left.begin(),left.end());
        vector<VarName> right=getAllConstantHelper(binNode.getRightExpr());
        vec1.insert(vec1.end(),right.begin(),right.end());
    }
    return vec1;
}

vector<VarName> BinaryOperatorNode::getAllVarFnHelper(Factor e){
    vector<VarName> vec1;

    if(VariableNode** v = std::get_if<VariableNode*>(&e)){
        VariableNode varNode = **v;
        vec1.push_back(varNode.getVariableName());
    }else if (BinaryOperatorNode** b = std::get_if<BinaryOperatorNode*>(&e)){
        BinaryOperatorNode binNode = **b;
        vector<VarName> left = getAllVarFnHelper(binNode.getLeftExpr());
        vec1.insert(vec1.begin(),left.begin(),left.end());
        vector<VarName> right=getAllVarFnHelper(binNode.getRightExpr());
        vec1.insert(vec1.end(),right.begin(),right.end());
    }
    return vec1;
}
