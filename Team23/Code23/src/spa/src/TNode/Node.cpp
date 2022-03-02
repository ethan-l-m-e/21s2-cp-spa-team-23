//
// Created by Tin Hong Wen on 28/1/22.
//
#include <iostream>
#include "TNode/Node.h"

using namespace std;

Node::Node() { this->parent = nullptr; }

void Node::setParentNode(Node *parent) {this -> parent = parent;}
Node *Node::getParentNode() const {return this -> parent;}
bool Node::hasStmtLst() {return false;}
StatementList Node::getStmtLst() {return {};}
int Node::getStmtNumber() const {return -1;}

vector<VarName> Node::getListOfVarUsed() {return {};}
vector<VarName> Node::getListOfVarModified() {return {};}
vector<VarName> Node::getAllVariables() {return {};}
vector<Constant> Node::getAllConstants() { return {};}

/*
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
*/






