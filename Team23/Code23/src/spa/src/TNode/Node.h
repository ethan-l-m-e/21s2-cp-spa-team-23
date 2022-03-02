//
// Created by Tin Hong Wen on 28/1/22.
//
#pragma once
#include <string>
#include <vector>
#include <variant>

#include "regex.h"

#ifndef SPA_NODE_H
#define SPA_NODE_H

using namespace std;

class Node;
typedef std::vector<Node *> StatementList;

typedef std::string VarName, ProcName, Constant;
using stmtNo = int;

class Node {
    Node* parent;
public:
    Node();
    void setParentNode(Node *parent);
    Node *getParentNode() const;

    virtual bool hasStmtLst();
    virtual vector<Node *> getStmtLst();
    virtual int getStmtNumber() const;
    virtual vector<VarName> getListOfVarUsed();
    virtual vector<VarName> getListOfVarModified();
    virtual vector<VarName> getAllVariables();
    virtual vector<VarName> getAllConstants();
};

#endif //SPA_NODE_H
