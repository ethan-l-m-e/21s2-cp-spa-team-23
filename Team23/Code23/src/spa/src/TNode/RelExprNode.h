//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_RELEXPRNODE_H
#define SPA_RELEXPRNODE_H

#include "Node.h"
#include "BinaryOperatorNode.h"

// Definition:
// rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
//          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
//          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
class RelExprNode : public Node {
    RelFactor leftNode;
    RelFactor rightNode;
    string relativeOperator;
public:
    RelExprNode(RelFactor leftNode, RelFactor rightNode, string relativeOperator);
    [[nodiscard]] RelFactor getLeftFactor() const;
    [[nodiscard]] RelFactor getRightFactor() const;
    [[nodiscard]] string getRelativeOperator() const;
    vector<VarName>  getAllVariables() override;
    vector<VarName> getAllConstants() override;
};

#endif //SPA_RELEXPRNODE_H
