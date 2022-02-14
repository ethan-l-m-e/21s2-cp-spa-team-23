//
// Created by Tin Hong Wen on 28/1/22.
//
#pragma once
#include <string>
#include <vector>
#include <variant>

#include "regex.h"
using namespace std;

#ifndef SPA_NODE_H
#define SPA_NODE_H

//define node
// node contains:
//    value | constant | operator
//    stmtNo
//    list of pointers to other nodes (i hate pointers)

typedef std::string VarName, ProcName;

class Node {
    Node* parent;
public:
    Node();
    void setParentNode(Node *parent);
    Node *getParentNode() const;
};

class StmtNode: public Node {
    int statementNumber;
public:
    StmtNode(int num);
    int getStmtNumber() const;
};

typedef std::vector<StmtNode *> StatementList;

class VariableNode: public Node {
public:
    VariableNode(VarName name);
    VarName& getVariableName();
private:
    VarName varName;
};

class ProcNameNode: public Node {
public:
    ProcNameNode(ProcName name);
    ProcName getProcedureName();
private:
    ProcName procedureName;
};

class ConstValueNode: public Node {
public:
    ConstValueNode(const string num);
    string getConstValue();
private:
    string constValue;
};




/*
class ReadNode: public StmtNode {
    VariableNode *varNode;
public:
    ReadNode(int, VariableNode*);
    VariableNode* getVarName() const;
};
*/
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

class AssignNode: public StmtNode {
    VariableNode *leftNode;
    Expression rightNode;
public:
    explicit AssignNode(int num, VariableNode *leftNode, Expression rightNode);
    VariableNode* getLeftNode() const;
    Expression getRightNode() const;
};

class BinaryOperatorNode : public Node {
    Expression leftExpr;
    Expression rightExpr;
    string binaryOperator;
public:
    BinaryOperatorNode(Expression leftExpr, Expression rightExpr, string binaryOperator);
    [[nodiscard]] Expression getLeftExpr() const;
    [[nodiscard]] Expression getRightExpr() const;
    [[nodiscard]] string getBinaryOperator() const;
};

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
};

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
};

// Definition:
// while: 'while' '(' cond_expr ')' '{' stmtLst '}'
class WhileNode: public Node {
    CondExprNode *condExpr;
    StatementList stmtLst;
public:
    WhileNode(CondExprNode *condExpr, StatementList stmtLst);
    CondExprNode *getCondExpr();
    StatementList getStmtLst();
};

class ProcedureNode: public Node {
    ProcNameNode *procName;
    StatementList stmtLst;
public:
    ProcedureNode(ProcNameNode *procName, StatementList stmtLst);
    ProcName getProcName();
    StatementList getStmtLst();
};

typedef std::vector<ProcedureNode*> Program;

#endif //SPA_NODE_H
