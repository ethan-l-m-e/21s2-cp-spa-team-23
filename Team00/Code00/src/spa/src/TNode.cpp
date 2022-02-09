//
// Created by Tin Hong Wen on 28/1/22.
//
#include <iostream>
#include "TNode.h"

using namespace std;


Node::Node() { this->parent = nullptr; }

void Node::setParentNode(Node *parent) {this -> parent = parent;}
Node *Node::getParentNode() const {return this -> parent;}


StmtNode::StmtNode(int num) { this ->statementNumber = num;}
int StmtNode::getStmtNumber() const { return this ->statementNumber; }

VariableNode::VariableNode(VarName name) { this ->varName = name; }
VarName &VariableNode::getVariableName(){ return this ->varName; }

ConstValueNode::ConstValueNode(const string num) { this -> constValue = num; }
string ConstValueNode::getConstValue() {return this ->constValue; }


AssignNode::AssignNode(int num, VariableNode *leftNode, VariableNode *rightNode) : StmtNode(num) {
    this ->leftNode = leftNode;
    this ->rightNode = rightNode;
    this ->leftNode ->setParentNode(this);
    this ->rightNode ->setParentNode(this);
}

VariableNode* AssignNode::getLeftNode() const {
    return this ->leftNode;
}

VariableNode* AssignNode::getRightNode() const {
    return this ->rightNode;
}

BinaryOperatorNode::BinaryOperatorNode(Expression *leftExpr, Expression *rightExpr, string binaryOperator) {
    this->leftExpr = leftExpr;
    this->rightExpr = rightExpr;
    this->binaryOperator = std::move(binaryOperator);
}

Expression *BinaryOperatorNode::getLeftExpr() const {
    return this->leftExpr;
}

Expression *BinaryOperatorNode::getRightExpr() const {
    return this->rightExpr;
}

RelExprNode::RelExprNode(RelFactor *leftNode, RelFactor *rightNode, string relativeOperator) {
    this->leftNode = leftNode;
    this->rightNode = rightNode;
    this->relativeOperator = std::move(relativeOperator);
}

RelFactor *RelExprNode::getLeftFactor() const {
    return this->leftNode;
}

RelFactor *RelExprNode::getRightFactor() const {
    return this->rightNode;
}

CondExprNode::CondExprNode(RelExprNode *relExpr){
    this->relExpr = relExpr;
}

CondExprNode::CondExprNode(CondExprNode *singleCondExpr) {
    this->condOperator = "!";
    this->rightNode = singleCondExpr;
}

CondExprNode::CondExprNode(string condOperator, CondExprNode *leftNode, CondExprNode *rightNode) {
    this->condOperator = std::move(condOperator);
    this->leftNode = leftNode;
    this->rightNode = rightNode;
}

CondExprNode *CondExprNode::getLeftNode() const {
    return this->leftNode;
}

CondExprNode *CondExprNode::getRightNode() const {
    return this->rightNode;
}

WhileNode::WhileNode(CondExprNode *condExpr, StatementList stmtLst) {
    this->condExpr = condExpr;
    this->stmtLst = std::move(stmtLst);
}

CondExprNode *WhileNode::getCondExpr() {
    return this->condExpr;
}

StatementList WhileNode::getStmtLst() {
    return this->stmtLst;
}
