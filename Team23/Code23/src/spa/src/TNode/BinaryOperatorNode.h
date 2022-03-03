//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_BINARYOPERATORNODE_H
#define SPA_BINARYOPERATORNODE_H

#include "Node.h"
#include "VariableNode.h"
#include "ConstValueNode.h"

class BinaryOperatorNode;
// Expression is replaced by BinaryOperatorNode***
// ***Explanation: expr is also a BinaryOperatorNode, VariableNode, or ConstValueNode
// factor: var_name | const_value | '(' expr ')'
using Factor = variant<VariableNode*, ConstValueNode*, BinaryOperatorNode*>;

// Term, Expression and RelFactor are all equated to Factor
// ***Explanation:
// term, expr are both either BinaryOperatorNodes, or they can become VariableNodes or ConstValueNodes
// rel_factor is already either VariableNode or ConstValueNode, but can also be an expr.
// Therefore, all three are actually the same as factor.

// term: term '*' factor | term '/' factor | term '%' factor | factor
using Term = Factor;
// expr: expr '+' term | expr '-' term | term
using Expression = Term;
// rel_factor: var_name | const_value | expr
using RelFactor = Expression;

class BinaryOperatorNode : public Node {
    Expression leftExpr;
    Expression rightExpr;
    string binaryOperator;

public:
    BinaryOperatorNode(Expression leftExpr, Expression rightExpr, string binaryOperator);
    [[nodiscard]] Expression getLeftExpr() const;
    [[nodiscard]] Expression getRightExpr() const;
    [[nodiscard]] string getBinaryOperator() const;

    static vector<Constant> getAllConstantHelper(Factor e); //TODO: refactor later?
    static vector<VarName> getAllVarFnHelper(Factor e); //TODO: refactor later?
};

#endif //SPA_BINARYOPERATORNODE_H
