//
// Created by リム・イーサン on 2/3/22.
//

#include "ProgramNode.h"

ProgramNode::ProgramNode(ProcedureList procLst) {
    this->procLst = procLst;
}

ProcedureList ProgramNode::getProcLst() {
    return this->procLst;
}
