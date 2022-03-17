//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "CallStatementTable.h"


string CallStatementTable::getProcedureName(string statementNumber) {

    CallNode *callNode = this->getNode(std::stoi(statementNumber));

    return callNode->getProcName();
}