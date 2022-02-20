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

typedef std::string VarName, ProcName, Constant;
using stmtNo = int;
class AssignNode;
class Node {
    Node* parent;
public:
    Node();
    void setParentNode(Node *parent);
    Node *getParentNode() const;

    virtual bool hasStmtLst();
    virtual vector<Node *> getStmtLst();
    virtual int getStmtNumber() const;
    virtual vector<VarName> getListOfVarUsed();
    virtual vector<VarName> getListOfVarModified();
    virtual vector<VarName> getAllVariables();
    virtual vector<VarName> getAllConstants();
};

//stmt: read | print | while | if | assign
class StmtNode: public Node {
    int statementNumber;
public:
    StmtNode(int num);
    int getStmtNumber() const override;
};

typedef std::vector<Node *> StatementList;

class StmtLstNode: public StmtNode{
    StatementList stmtLst;
public:
    StmtLstNode(int num, StatementList stmtLst);
    vector<Node *> getStmtLst() override;
    //vector<VarName> getListOfVarUsed() override;
    //vector<VarName> getListOfVarModified() override;

    bool hasStmtLst() override;
};

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


// Definition:
// read: 'read' var_name';'
class ReadNode: public StmtNode {
    VariableNode *varNode;
public:
    ReadNode(int num, VariableNode* varNode);
    [[nodiscard]] VarName getVarName() const;
    vector<VarName> getListOfVarModified() override;
};

// Definition:
// print: 'print' var_name';'
class PrintNode: public StmtNode {
    VariableNode *varNode;
public:
    PrintNode(int num, VariableNode* varNode);
    [[nodiscard]] VarName getVarName() const;
    vector<VarName> getListOfVarUsed() override;
};

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
    vector<VarName> getListOfVarUsed() override;
    vector<VarName> getListOfVarModified() override;
    vector<VarName> getAllVariables() override;
    vector<Constant> getAllConstants() override;
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
    vector<VarName>  getAllVariables() override;
    vector<VarName> getAllConstants() override;
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
    vector<VarName>  getListOfVarUsed() override;
    vector<VarName>  getAllVariables() override;
    vector<Constant> getAllConstants() override;
};

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
    //vector<stmtNo> getAllIfStmtNo() override;
};

class ProcedureNode: public StmtLstNode {
    ProcNameNode *procName;
    StatementList stmtLst;
public:
    ProcedureNode(ProcNameNode *procName, StatementList stmtLst);
    ProcName getProcName();
    //vector<ProcName> getAllProcedure() override;
};

typedef std::vector<ProcedureNode*> ProcedureList;

class ProgramNode: public Node {
    ProcedureList procLst;
public:
    ProgramNode(ProcedureList procLst);
    ProcedureList getProcLst();
};

#endif //SPA_NODE_H
