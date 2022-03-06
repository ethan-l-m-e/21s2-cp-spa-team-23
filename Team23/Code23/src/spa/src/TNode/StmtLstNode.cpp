//
// Created by リム・イーサン on 2/3/22.
//

#include "StmtLstNode.h"

bool StmtLstNode::hasStmtLst() {return true;}
StmtLstNode::StmtLstNode(int num, StatementList lst):StmtNode(num) {stmtLst=lst;}
vector<Node *> StmtLstNode::getStmtLst() {return this->stmtLst;}
