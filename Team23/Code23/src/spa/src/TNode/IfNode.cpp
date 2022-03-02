//
// Created by リム・イーサン on 2/3/22.
//

#include "IfNode.h"

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

bool IfNode::hasStmtLst(){
    return true;
}

StatementList IfNode::getStmtLst() {
    StatementList combinedStmtLst;
    combinedStmtLst.insert( combinedStmtLst.end(), this->thenStmtLst.begin(), this->thenStmtLst.end() );
    combinedStmtLst.insert( combinedStmtLst.end(), this->elseStmtLst.begin(), this->elseStmtLst.end() );
    return combinedStmtLst;
}
