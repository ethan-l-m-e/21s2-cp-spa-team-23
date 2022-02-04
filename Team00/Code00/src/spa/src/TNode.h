//
// Created by Tin Hong Wen on 28/1/22.
//
#pragma once
#include <string>
#include <vector>

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
    vector<TNode> childrenRef;
    int stmtNo;
public:
    TNode(string);
    TNode(string, int);
    void addNode(TNode &);
    void removeNode(int);
    TNode getNode(int);
    string getValue();
    void changeValue(string value);
    bool hasStmtNo();
    int getStmtNo();
    void setStmtNo(int);

};
#endif //SPA_NODE_H
