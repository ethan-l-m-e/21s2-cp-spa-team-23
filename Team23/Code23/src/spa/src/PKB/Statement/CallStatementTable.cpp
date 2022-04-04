//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "CallStatementTable.h"



void CallStatementTable::addStatement(CallNode *node) {
    StatementTable<CallNode *>::addStatement(node);

    statementNumberToProcedureNameMap.emplace(node->getStmtNumber(), node->getProcName());

}

string CallStatementTable::getProcedureName(string statementNumber) {

    return statementNumberToProcedureNameMap[std::stoi(statementNumber)];
}

void CallStatementTable::clear() {
    StatementTable<CallNode *>::clear();
    statementNumberToProcedureNameMap.clear();
}