//
// Created by リム・イーサン on 2/3/22.
//

#include "WhileNode.h"

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
