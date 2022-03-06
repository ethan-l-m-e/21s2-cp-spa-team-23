//
// Created by リム・イーサン on 2/3/22.
//

#include "ProgramNode.h"

ProgramNode::ProgramNode(ProcedureList procLst) {
    this->procLst = std::move(procLst);
    for (Node *procNode : this->procLst) {
        procNode->setParentNode(this);
    }
}

ProcedureList ProgramNode::getProcLst() {
    return this->procLst;
}
