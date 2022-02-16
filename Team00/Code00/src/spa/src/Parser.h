#pragma once
#include "TNode.h"

using namespace std;

class Parser {
public:
    static int Parse(string);

    static VariableNode* parseVar(string variable);
    static ConstValueNode* parseConst(string constValue);
    static ProcNameNode* parseProcName(string procedureName);

    static StmtNode* parseStatementNode(string * stmt);
    /*
    static PrintNode* parsePrint(string printLine);
    static ReadNode* parseRead(string readLine);
    static IfNode* parseIf(string code);

     */
    static WhileNode* parseWhile(string code);
    static AssignNode* parseAssign(string assignLine);
    static StatementList parseStatementList(string stmtList);
    static ProcedureNode* parseProcedure(string * procedure);
    static Program parseProgram(string sourceCode);
};

