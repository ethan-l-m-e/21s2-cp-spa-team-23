//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "StatementTable.h"
#include "TNode/TNode.h"

class CallStatementTable : public StatementTable<CallNode *> {

private:
    unordered_map<int, string> statementNumberToProcedureNameMap;

public:
    void addStatement(CallNode *node);

    string getProcedureName(string statementNumber);
};
