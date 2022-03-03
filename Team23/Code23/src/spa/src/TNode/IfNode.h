//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_IFNODE_H
#define SPA_IFNODE_H

#include "StmtNode.h"
#include "CondExprNode.h"

// Definition:
// if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
class IfNode: public StmtNode {
    CondExprNode *condExpr;
    StatementList thenStmtLst;
    StatementList elseStmtLst;
public:
    IfNode(int num, CondExprNode *condExpr, StatementList thenStmtLst, StatementList elseStmtLst);
    CondExprNode *getCondExpr();
    StatementList getThenStmtLst();
    StatementList getElseStmtLst();
    StatementList getStmtLst() override;
    bool hasStmtLst() override;
};

#endif //SPA_IFNODE_H
