//
// Created by Tin Hong Wen on 28/1/22.
//
#include <iostream>
#include "TNode.h"

using namespace std;
/**
 * TNode is obsolete, remove TNode methods (safely of course) and use Node instead!
 **/

TNode::TNode(string name) {
    this -> value = name;
}

TNode::TNode(string name, int stmtNo) {
    this -> value = name;
    this -> stmtNo = stmtNo;
}

void TNode::addNode(TNode *nodeRef) {
    // add node ref into the childrenRef
    childrenRef.push_back(nodeRef);
}

TNode *TNode::getNode(int index) {
    return childrenRef[index];
}

int TNode::getNumberOfChildNodes() {
    return childrenRef.size();
}

string TNode::getValue() {
    return value;
}

void TNode::changeValue(string value) {
    this -> value = value;
}

bool TNode::hasStmtNo() {
    if (this -> stmtNo > 0)
        return true;
    else
        return false;
}

int TNode::getStmtNo() {
    return stmtNo;
}

void TNode::setStmtNo(int stmtNo) {
    this -> stmtNo = stmtNo;
}



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