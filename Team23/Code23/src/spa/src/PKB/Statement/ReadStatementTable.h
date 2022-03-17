//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "StatementTable.h"
#include "TNode/TNode.h"

class ReadStatementTable : public StatementTable<ReadNode *> {
public:
    string getVariableName(string statementNumber);
};

