//
// Created by Karan Dev Sapra on 17/3/22.
//


#include "StatementTable.h"
#include "TNode/TNode.h"

class ReadStatementTable : public StatementTable<ReadNode *> {

private:
    unordered_map<int, string> statementNumberToVariableNameMap;

public:
    void addStatement(ReadNode *node);

    string getVariableName(string statementNumber);

    void clear() override;
};

