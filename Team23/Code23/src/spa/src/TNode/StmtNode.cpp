//
// Created by リム・イーサン on 2/3/22.
//

#include "StmtNode.h"

StmtNode::StmtNode(int num) {
    this ->statementNumber = num;
    this->proc = nullptr;
}
int StmtNode::getStmtNumber() const { return this ->statementNumber; }
void StmtNode::setProc(Node *proc){this->proc = proc;}
Node *StmtNode::getProc() const{return this->proc;}

