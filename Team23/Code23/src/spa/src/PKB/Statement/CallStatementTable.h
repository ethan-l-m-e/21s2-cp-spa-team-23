//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "StatementTable.h"
#include "TNode/TNode.h"

class CallStatementTable : public StatementTable<CallNode *> {
public:
    string getProcedureName(string statementNumber);
};

