//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "Statement.h"
#include "TNode/TNode.h"

class PrintStatementTable : public StatementTable<PrintNode *> {

    string getVariableName(string statementNumber);
};

