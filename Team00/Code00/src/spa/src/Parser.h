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

    static AssignNode* parseAssign(string assignLine);
    static StatementList parseStatementList(string stmtList);
    ProcedureNode* parseProcedure(string procedure);
};

