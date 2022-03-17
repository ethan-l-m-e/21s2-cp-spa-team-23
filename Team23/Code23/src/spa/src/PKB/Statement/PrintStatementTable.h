//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "StatementTable.h"
#include "TNode/TNode.h"

class PrintStatementTable : public StatementTable<PrintNode *> {

private:
    unordered_map<int, string> statementNumberToVariableNameMap;

public:

    void addStatement(PrintNode *node);

    string getVariableName(string statementNumber);
};