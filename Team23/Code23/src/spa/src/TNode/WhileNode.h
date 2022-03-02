//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_WHILENODE_H
#define SPA_WHILENODE_H

#include "StmtLstNode.h"
#include "CondExprNode.h"
#include "Node.h"

// Definition:
// while: 'while' '(' cond_expr ')' '{' stmtLst '}'
class WhileNode: public StmtLstNode {
    CondExprNode *condExpr;
    StatementList stmtLst;
public:
    WhileNode(int num, CondExprNode *condExpr, StatementList stmtLst);
    CondExprNode *getCondExpr();
    //vector<stmtNo> getAllWhileStmtNo() override;
};

#endif //SPA_WHILENODE_H
