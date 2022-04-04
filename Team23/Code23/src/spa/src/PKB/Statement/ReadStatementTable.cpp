//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "ReadStatementTable.h"


void ReadStatementTable::addStatement(ReadNode *node) {
    StatementTable<ReadNode *>::addStatement(node);

    statementNumberToVariableNameMap.emplace(node->getStmtNumber(), node->getVarName());

}

string ReadStatementTable::getVariableName(string statementNumber) {

    return statementNumberToVariableNameMap[std::stoi(statementNumber)];
}


void ReadStatementTable::clear() {
    StatementTable<ReadNode*>::clear();
    statementNumberToVariableNameMap.clear();
}