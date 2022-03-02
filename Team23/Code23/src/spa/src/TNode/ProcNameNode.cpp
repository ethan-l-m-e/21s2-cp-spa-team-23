//
// Created by リム・イーサン on 2/3/22.
//

#include "ProcNameNode.h"

ProcNameNode::ProcNameNode(ProcName name) {
    this->procedureName = std::move(name);
}

ProcName ProcNameNode::getProcedureName() {
    return this->procedureName;
}

