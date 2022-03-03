//
// Created by リム・イーサン on 2/3/22.
//

#include "CondExprNode.h"

CondExprNode::CondExprNode(RelExprNode *relExpr){
    this->relExpr = relExpr;
    this->relExpr->setParentNode(this);
}

CondExprNode::CondExprNode(CondExprNode *singleCondExpr) {
    this->condOperator = "!";
    this->rightNode = singleCondExpr;
    this->rightNode->setParentNode(this);
}

CondExprNode::CondExprNode(string condOperator, CondExprNode *leftNode, CondExprNode *rightNode) {
    this->condOperator = std::move(condOperator);
    this->leftNode = leftNode;
    this->leftNode->setParentNode(this);
    this->rightNode = rightNode;
    this->rightNode->setParentNode(this);
}

RelExprNode *CondExprNode::getRelExpr() const {
    return this->relExpr;
}

CondExprNode *CondExprNode::getLeftNode() const {
    return this->leftNode;
}

CondExprNode *CondExprNode::getRightNode() const {
    return this->rightNode;
}

string CondExprNode::getCondOperator() const {
    return this->condOperator;
}

vector<VarName> CondExprNode::getListOfVarUsed() {
    return this->getAllVariables();
}

vector<VarName> CondExprNode::getAllVariables() {
    vector<VarName> vector1;
    // Case: rel_expr
    if (this->getCondOperator().empty()) {
        vector1 = this->relExpr->getAllVariables();
        return vector1;
    }
    // Case: '!' '(' cond_expr ')'
    if (this->getCondOperator() == "!") {
        vector1 = this->rightNode->getAllVariables();
        return vector1;
    }
    // Case: '(' cond_expr ')' '&&' '(' cond_expr ')' |'(' cond_expr ')' '||' '(' cond_expr ')'
    vector1 = this->leftNode->getAllVariables();
    vector<VarName> vector2 = this->rightNode->getAllVariables();
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}

vector<Constant> CondExprNode::getAllConstants() {
    vector<Constant> vector1;
    // Case: rel_expr
    if (this->getCondOperator().empty()) {
        vector1 = this->relExpr->getAllConstants();
        return vector1;
    }
    // Case: '!' '(' cond_expr ')'
    if (this->getCondOperator() == "!") {
        vector1 = this->rightNode->getAllConstants();
        return vector1;
    }
    // Case: '(' cond_expr ')' '&&' '(' cond_expr ')' |'(' cond_expr ')' '||' '(' cond_expr ')'
    vector1 = this->leftNode->getAllVariables();
    vector<Constant> vector2 = this->rightNode->getAllConstants();
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}
