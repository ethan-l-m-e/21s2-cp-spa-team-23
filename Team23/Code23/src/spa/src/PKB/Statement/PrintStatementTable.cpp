//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "PrintStatementTable.h"


string PrintStatementTable::getVariableName(string statementNumber) {

    PrintNode *printNode = this->getNode(std::stoi(statementNumber));

    return printNode->getVarName();
}