//
// Created by リム・イーサン on 2/3/22.
//

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(ProcNameNode *procName, StatementList stmtLst)
        : StmtLstNode(-1, stmtLst) {
    this->procName = procName;
    this->stmtLst = std::move(stmtLst);
    for (Node *stmtNode : this->stmtLst) {
        stmtNode->setParentNode(this);
    }
}

ProcName ProcedureNode::getProcName() {
    return this->procName->getProcedureName();
}
