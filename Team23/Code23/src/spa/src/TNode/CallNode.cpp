//
// Created by リム・イーサン on 5/3/22.
//

#include "CallNode.h"

CallNode::CallNode(int num, ProcNameNode *procNameNode): StmtNode(num) {
    this->procNameNode = procNameNode;
}

ProcName CallNode::getProcName() const {
    return this->procNameNode->getProcedureName();
}

Node* CallNode::getProcedure() {
    ProcedureList lst = getProcLst();
    ProcName pr = this->getProcName();
    for(ProcedureNode *node : lst) {
        if (node->getProcName() == pr) {
            return node;
        }
    }
    throw "No procedure with this name found";
}

ProcedureList CallNode::getProcLst() {
    Node* p = this;
    while(true) {
        if(auto value = dynamic_cast<ProgramNode*>(p)) {
            return value->getProcLst();
        }
        p = p->getParentNode();
    }
}
