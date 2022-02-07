//
// Created by Tin Hong Wen on 28/1/22.
//
#pragma once
#include <string>
#include <vector>

#include "regex.h"
using namespace std;

#ifndef SPA_NODE_H
#define SPA_NODE_H

//define node
// node contains:
//    value | constant | operator
//    stmtNo
//    list of pointers to other nodes (i hate pointers)



class TNode {
    string value; // can be value, constant or integer constant and integer have to be converted back into int first for proper use
    vector<TNode*> childrenRef;
    int stmtNo = -1;

public:
    TNode(string);
    TNode(string, int);
    void addNode(TNode*);
    TNode* getNode(int);
    int getNumberOfChildNodes();
    string getValue();
    void changeValue(string value);

    bool hasStmtNo();
    int getStmtNo();
    void setStmtNo(int);

};





typedef std::string VarName, ProcName;

class Node {
    Node* parent;
public:
    Node();
    void setParentNode(Node *parent);
    Node *getParentNode() const;
};

class StmtNode: public Node {
    int statementNumber;
public:
    StmtNode(int num);
    int getStmtNumber() const;
};

typedef std::vector<StmtNode *> StatementList;

class VariableNode: public Node {
public:
    VariableNode(VarName name);
    VarName& getVariableName();
private:
    VarName varName;
};

class ProcNameNode: public Node {
public:
    ProcNameNode(ProcName name);
    ProcName getProcedureName();
private:
    ProcName procedureName;
};

class ConstValueNode: public Node {
public:
    ConstValueNode(const string num);
    string getConstValue();
private:
    string constValue;
};


class AssignNode: public StmtNode {
    VariableNode *leftNode;
    VariableNode *rightNode;
public:
    explicit AssignNode(int num, VariableNode *leftNode, VariableNode *rightNode);
    VariableNode* getLeftNode() const;
    VariableNode* getRightNode() const;
};

/*
class ReadNode: public StmtNode {
    VariableNode *varNode;
public:
    ReadNode(int, VariableNode*);
    VariableNode* getVarName() const;
};
*/

class ProcedureNode: public Node {
    ProcNameNode *procName;
    StatementList stmtLst;
public:
    ProcedureNode(ProcName *procName, StatementList stmtLst);
    ProcName getProcName();
    StatementList getStmtLst();
};

#endif //SPA_NODE_H
