#pragma once
#include "TNode/Node.h"
#include "TNode/ProgramNode.h"
#include "TNode/AssignNode.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
#include "TNode/ReadNode.h"
#include "TNode/PrintNode.h"
#include "TNode/CallNode.h"

using namespace std;

class InvalidSyntacticException : public std::runtime_error {
public:
    InvalidSyntacticException(const std::string& message = "") : std::runtime_error(message) {}
};

class Parser {
public:
    static Node* Parse(string);

    static VariableNode* parseVar(string variable);
    static ConstValueNode* parseConst(string constValue);
    static ProcNameNode* parseProcName(string procedureName);

    static CondExprNode* parseCondExpr(string condExprLine);
    static RelExprNode* parseRelExpr(string relExprLine);
    static StmtNode* parseStatementNode(string * stmt);

    static CallNode* parseCall(string callLine);
    static ReadNode* parseRead(string readLine);
    static PrintNode* parsePrint(string printLine);
    static IfNode* parseIf(string code);

    static WhileNode* parseWhile(string code);
    static AssignNode* parseAssign(string assignLine);
    static StatementList parseStatementList(string stmtList);
    static ProcedureNode* parseProcedure(string * procedure);
    static ProgramNode* parseProgram(string sourceCode);

    static Expression parseExpression(string expression);

    static void resetStatementNumber();
};

