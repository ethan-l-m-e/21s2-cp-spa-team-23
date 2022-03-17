//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "Statement.h"
#include "TNode/TNode.h"

class CallStatementTable : public StatementTable<CallNode *> {

    string getProcedureName(string statementNumber);
};

