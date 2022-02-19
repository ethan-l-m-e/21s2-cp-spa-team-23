#pragma once
#include "TNode.h"

using namespace std;

class Parser {
public:
    static Node* Parse(string);

    static VariableNode* parseVar(string variable);
    static ConstValueNode* parseConst(string constValue);
    static ProcNameNode* parseProcName(string procedureName);

    static CondExprNode* parseCondExpr(string condExprLine);
    static RelExprNode* parseRelExpr(string relExprLine);
    static StmtNode* parseStatementNode(string * stmt);

    static ReadNode* parseRead(string readLine);
    static PrintNode* parsePrint(string printLine);
    static IfNode* parseIf(string code);

    static WhileNode* parseWhile(string code);
    static AssignNode* parseAssign(string assignLine);
    static StatementList parseStatementList(string stmtList);
    static ProcedureNode* parseProcedure(string * procedure);
    static Program parseProgram(string sourceCode);

    static Expression parseExpression(string expression);
};

