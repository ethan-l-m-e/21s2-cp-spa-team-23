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
int Node::getStmtNumber() const {return -1;}
vector<string> Node::getListOfVarUsed() {return {};}
vector<string> Node::getListOfVarModified() {return {};}

vector<VarName> Node::getAllVariables() {return {};}
vector<ProcName> Node::getAllProcedure() { return {};};
vector<Constant> Node::getAllConstants() { return {};};
vector<stmtNo> Node::getAllStatementNumber() { return {};}
vector<stmtNo> Node::getAllReadStmt() { return {};}
vector<stmtNo> Node::getAllPrintStmt() { return {};}
vector<stmtNo> Node::getAllAssignStmt() { return {};}
vector<AssignNode*> Node::getAllAssignNodes() {return {};}
vector<stmtNo> Node::getAllWhileStmtNo() { return {};}
vector<stmtNo> Node::getAllIfStmtNo() { return {};}

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

vector<VarName> ReadNode::getAllVariables() {
    return vector<VarName> {this->varNode->getVariableName()};
}

vector<VarName> ReadNode::getListOfVarModified() {
    return this->getAllVariables();
}

vector<stmtNo> ReadNode::getAllReadStmt() {
    return vector<stmtNo>{this->getStmtNumber()};
}

PrintNode::PrintNode(int num, VariableNode *varNode): StmtNode(num) {
    this->varNode = varNode;
    this->varNode->setParentNode(this);
}

VarName PrintNode::getVarName() const {
    return this->varNode->getVariableName();
}

vector<VarName> PrintNode::getAllVariables() {
    return vector<VarName> {this->varNode->getVariableName()};
}

vector<VarName> PrintNode::getListOfVarUsed() {
    return this->getAllVariables();
}

vector<stmtNo> PrintNode::getAllPrintStmt() {
    return vector<stmtNo>{this->getStmtNumber()};
}


bool StmtLstNode::hasStmtLst() {return true;}
StmtLstNode::StmtLstNode(int num, StatementList lst):StmtNode(num) {stmtLst=lst;}
vector<Node *> StmtLstNode::getStmtLst() {return this->stmtLst;}

vector<VarName> StmtLstNode::getListOfVarUsed() {
    vector<VarName> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<VarName> list = getStmtLst().at(i)->getListOfVarUsed();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    return toReturn;
}
vector<VarName> StmtLstNode::getListOfVarModified() {
    vector<VarName> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<VarName> list = getStmtLst().at(i)->getListOfVarModified();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}


vector<VarName> StmtLstNode::getAllVariables() {
    vector<VarName> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<VarName> list = getStmtLst().at(i)->getAllVariables();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

vector<VarName> StmtLstNode::getAllConstants() {
    vector<Constant> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<Constant> list = getStmtLst().at(i)->getAllConstants();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

vector<stmtNo> StmtLstNode::getAllReadStmt() {
    vector<stmtNo> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<stmtNo> list = getStmtLst().at(i)->getAllReadStmt();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

vector<stmtNo> StmtLstNode::getAllPrintStmt() {
    vector<stmtNo> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<stmtNo> list = getStmtLst().at(i)->getAllPrintStmt();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

vector<stmtNo> StmtLstNode::getAllAssignStmt() {
    vector<stmtNo> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<stmtNo> list = getStmtLst().at(i)->getAllAssignStmt();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

vector<AssignNode*> StmtLstNode::getAllAssignNodes() {
    vector<AssignNode*> toReturn;
    for(int i = 0; i < getStmtLst().size() ; i++) {
        vector<AssignNode*> list = getStmtLst().at(i)->getAllAssignNodes();
        toReturn.insert(toReturn.end(),
                        list.begin(),
                        list.end());
    }
    //cout<<toReturn.at(0);
    return toReturn;
}

AssignNode::AssignNode(int num, VariableNode *leftNode, Expression rightNode) : StmtNode(num) {
    this ->leftNode = leftNode;
    this ->rightNode = rightNode;
    this ->leftNode ->setParentNode(this);
    visit([this](auto& n){n->setParentNode(this);},this->rightNode);
}

vector<Constant> getAllConstantHelper(Factor e) {
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

vector<VarName> AssignNode::getListOfVarUsed(){
    return getAllVarFnHelper(this->getRightNode());
}
vector<VarName> AssignNode::getListOfVarModified(){
    vector<string> v = getAllVarFnHelper(this->getLeftNode());
    return v;
}
vector<VarName> AssignNode::getAllVariables() {
    vector<VarName> vector1 = AssignNode::getListOfVarModified();
    vector<VarName> vector2 = AssignNode::getListOfVarUsed();
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    return vector1;
}
vector<int> AssignNode::getAllAssignStmt() {
    return vector<int>{this->getStmtNumber()};
}
vector<AssignNode*> AssignNode::getAllAssignNodes() {
    return vector<AssignNode*> {this};
}
vector<Constant> AssignNode::getAllConstants() {
    return getAllConstantHelper(this->getRightNode());
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

WhileNode::WhileNode(int num, CondExprNode *condExpr, StatementList stmtLst) : StmtLstNode(num, stmtLst) {
    this->condExpr = condExpr;
    this->condExpr->setParentNode(this);
    this->stmtLst = std::move(stmtLst);
    for (Node *stmtNode : this->stmtLst) {
        stmtNode->setParentNode(this);
    }
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

IfNode::IfNode(int num, CondExprNode *condExpr, StatementList thenStmtLst, StatementList elseStmtLst): StmtNode(num) {
    this->condExpr = condExpr;
    condExpr->setParentNode(this);
    this->thenStmtLst = std::move(thenStmtLst);
    for (Node *thenNode: this->thenStmtLst) {
        thenNode->setParentNode(this);
    }
    this->elseStmtLst = std::move(elseStmtLst);
    for (Node *elseNode: this->elseStmtLst) {
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

ProcedureNode::ProcedureNode(ProcNameNode *procName, StatementList stmtLst)
        : StmtLstNode(-1, stmtLst) {
    this->procName = procName;
    this->stmtLst = std::move(stmtLst);
    for (Node *stmtNode : this->stmtLst) {
        stmtNode->setParentNode(this);
    }
}

ProcName ProcedureNode::getProcName() {
    return this->procName->getProcedureName();
}

ProgramNode::ProgramNode(ProcedureList procLst) {
    this->procLst = procLst;
}

ProcedureList ProgramNode::getProcLst() {
    return this->procLst;
}

//StatementList ProcedureNode::getStmtLst() {
//    return this->stmtLst;
//}
//
//bool ProcedureNode::hasStmtLst() {
//    return true;
//}
