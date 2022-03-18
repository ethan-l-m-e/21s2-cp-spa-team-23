//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "PrintStatementTable.h"


void PrintStatementTable::addStatement(PrintNode *node) {
    StatementTable<PrintNode *>::addStatement(node);

    statementNumberToVariableNameMap.emplace(node->getStmtNumber(), node->getVarName());

}

string PrintStatementTable::getVariableName(string statementNumber) {

    return statementNumberToVariableNameMap[std::stoi(statementNumber)];
}