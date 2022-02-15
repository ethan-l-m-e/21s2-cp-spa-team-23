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

ReadNode::ReadNode(int num, VariableNode *varNode): StmtNode(num) {
    this->varNode = varNode;
    this->varNode->setParentNode(this);
}

VarName ReadNode::getVarName() const {
    return this->varNode->getVariableName();
}

PrintNode::PrintNode(int num, VariableNode *varNode): StmtNode(num) {
    this->varNode = varNode;
    this->varNode->setParentNode(this);
}

VarName PrintNode::getVarName() const {
    return this->varNode->getVariableName();
}

AssignNode::AssignNode(int num, VariableNode *leftNode, Expression rightNode) : StmtNode(num) {
    this ->leftNode = leftNode;
    this ->rightNode = rightNode;
    this ->leftNode ->setParentNode(this);
    visit([this](auto& n){n->setParentNode(this);},this->rightNode);
}

VariableNode* AssignNode::getLeftNode() const {
    return this ->leftNode;
}

Expression AssignNode::getRightNode() const {
    return this ->rightNode;
}

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

WhileNode::WhileNode(int num, CondExprNode *condExpr, StatementList stmtLst): StmtNode(num) {
    this->condExpr = condExpr;
    this->condExpr->setParentNode(this);
    this->stmtLst = std::move(stmtLst);
    for (StmtNode *stmtNode : this->stmtLst) {
        stmtNode->setParentNode(this);
    }
}

CondExprNode *WhileNode::getCondExpr() {
    return this->condExpr;
}

StatementList WhileNode::getStmtLst() {
    return this->stmtLst;
}

IfNode::IfNode(int num, CondExprNode *condExpr, StatementList thenStmtLst, StatementList elseStmtLst): StmtNode(num) {
    this->condExpr = condExpr;
    condExpr->setParentNode(this);
    this->thenStmtLst = std::move(thenStmtLst);
    for (StmtNode *thenNode: this->thenStmtLst) {
        thenNode->setParentNode(this);
    }
    this->elseStmtLst = std::move(elseStmtLst);
    for (StmtNode *elseNode: this->elseStmtLst) {
        elseNode->setParentNode(this);
    }
}

CondExprNode *IfNode::getCondExpr() {
    return this->condExpr;
}

StatementList IfNode::getThenStmtLst() {
    return this->thenStmtLst;
}

StatementList IfNode::getElseStmtLst() {
    return this->elseStmtLst;
}

ProcNameNode::ProcNameNode(ProcName name) {
    this->procedureName = std::move(name);
}

ProcName ProcNameNode::getProcedureName() {
    return this->procedureName;
}

ProcedureNode::ProcedureNode(ProcNameNode *procName, StatementList stmtLst) {
    this->procName = procName;
    this->stmtLst = std::move(stmtLst);
    for (StmtNode *stmtNode : this->stmtLst) {
        stmtNode->setParentNode(this);
    }
}

ProcName ProcedureNode::getProcName() {
    return this->procName->getProcedureName();
}

StatementList ProcedureNode::getStmtLst() {
    return this->stmtLst;
}
