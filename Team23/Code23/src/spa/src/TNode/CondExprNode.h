//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_CONDEXPRNODE_H
#define SPA_CONDEXPRNODE_H

#include "Node.h"
#include "RelExprNode.h"

// Definition:
// cond_expr: rel_expr | '!' '(' cond_expr ')' |
//           '(' cond_expr ')' '&&' '(' cond_expr ')' |
//           '(' cond_expr ')' '||' '(' cond_expr ')'
class CondExprNode : public Node {
    RelExprNode *relExpr = nullptr;
    string condOperator = "";
    CondExprNode *leftNode = nullptr;
    CondExprNode *rightNode = nullptr;
public:
    // Case: rel_expr
    explicit CondExprNode(RelExprNode *relExpr);
    // Case: '!' '(' cond_expr ')'
    explicit CondExprNode(CondExprNode *singleCondExpr);
    // Case: '(' cond_expr ')' '&&' '(' cond_expr ')' |'(' cond_expr ')' '||' '(' cond_expr ')'
    CondExprNode(string condOperator, CondExprNode *leftNode, CondExprNode *rightNode);

    [[nodiscard]] RelExprNode *getRelExpr() const;
    [[nodiscard]] CondExprNode *getLeftNode() const;
    [[nodiscard]] CondExprNode *getRightNode() const;
    [[nodiscard]] string getCondOperator() const;
    vector<VarName>  getListOfVarUsed() override;
    vector<VarName>  getAllVariables() override;
    vector<Constant> getAllConstants() override;
};

#endif //SPA_CONDEXPRNODE_H
