//
// Created by Tin Hong Wen on 28/1/22.
//
#include <iostream>
#include "TNode.h"

using namespace std;


Node::Node() { this->parent = nullptr; }

void Node::setParentNode(Node *parent) {this -> parent = parent;}
Node *Node::getParentNode() const {return this -> parent;}
bool Node::hasStmtLst() {return false;}
StatementList Node::getStmtLst() {return {};}
int Node::getStmtNumber() const {return 0;}
vector<string> Node::getListOfVarUsed() {return {};}
vector<string> Node::getListOfVarModified() {return {};}

StmtNode::StmtNode(int num) { this ->statementNumber = num;}
int StmtNode::getStmtNumber() const { return this ->statementNumber; }

VariableNode::VariableNode(VarName name) { this ->varName = name; }
VarName &VariableNode::getVariableName(){ return this ->varName; }

ConstValueNode::ConstValueNode(const string num) { this -> constValue = num; }
string ConstValueNode::getConstValue() {return this ->constValue; }

bool StmtLstNode::hasStmtLst() {return true;}
StmtLstNode::StmtLstNode(int num, StatementList lst):StmtNode(num) {stmtLst=lst;}
vector<Node *> StmtLstNode::getStmtLst() {return this->stmtLst;}

vector<VarName> StmtLstNode::getListOfVarUsed() {
    vector<VarName> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        toReturn.insert(toReturn.end(),
                        getStmtLst().at(i)->getListOfVarUsed().begin(),
                        getStmtLst().at(i)->getListOfVarUsed().end());
    }
    return toReturn;
}
vector<VarName> StmtLstNode::getListOfVarModified() {
    vector<VarName> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        toReturn.insert(toReturn.end(),
                        getStmtLst().at(i)->getListOfVarModified().begin(),
                        getStmtLst().at(i)->getListOfVarModified().end());
    }
    return toReturn;
}

AssignNode::AssignNode(int num, VariableNode *leftNode, Expression rightNode) : StmtNode(num) {
    this ->leftNode = leftNode;
    this ->rightNode = rightNode;
    this ->leftNode ->setParentNode(this);
    visit([this](auto& n){n->setParentNode(this);},this->rightNode);
}

vector<VarName> getAllVarFnHelper(Factor e){
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

vector<string> AssignNode::getListOfVarUsed(){
    return getAllVarFnHelper(this->getRightNode());
}
vector<string> AssignNode::getListOfVarModified(){
    return getAllVarFnHelper(this->getLeftNode());
}

VariableNode* AssignNode::getLeftNode() const {
    return this ->leftNode;
}

Expression AssignNode::getRightNode() const {
    return this ->rightNode;
}

BinaryOperatorNode::BinaryOperatorNode(Expression leftExpr, Expression rightExpr, string binaryOperator) {
    this->leftExpr = leftExpr;
    this->rightExpr = rightExpr;
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
    this->rightNode = rightNode;
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

WhileNode::WhileNode(int num, CondExprNode *condExpr, StatementList stmtLst) : StmtLstNode(num, stmtLst) {
    this->condExpr = condExpr;
    this->stmtLst = std::move(stmtLst);
}

CondExprNode *WhileNode::getCondExpr() {
    return this->condExpr;
}

//bool WhileNode::hasStmtLst() {
//    return true;
//}
//
//StatementList WhileNode::getStmtLst() {
//    return this->stmtLst;
//}

ProcNameNode::ProcNameNode(ProcName name) {
    this->procedureName = std::move(name);
}

ProcName ProcNameNode::getProcedureName() {
    return this->procedureName;
}

ProcedureNode::ProcedureNode(int num, ProcNameNode *procName, StatementList stmtLst)
        : StmtLstNode(num, stmtLst) {
    this->procName = procName;
    this->stmtLst = std::move(stmtLst);
}

ProcName ProcedureNode::getProcName() {
    return this->procName->getProcedureName();
}

//StatementList ProcedureNode::getStmtLst() {
//    return this->stmtLst;
//}
//
//bool ProcedureNode::hasStmtLst() {
//    return true;
//}
