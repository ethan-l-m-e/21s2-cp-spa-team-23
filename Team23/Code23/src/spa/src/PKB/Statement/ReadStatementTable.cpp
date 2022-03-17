//
// Created by Karan Dev Sapra on 17/3/22.
//

#include "ReadStatementTable.h"


string ReadStatementTable::getVariableName(string statementNumber) {

    ReadNode *readNode = this->getNode(std::stoi(statementNumber));

    return readNode->getVarName();
}