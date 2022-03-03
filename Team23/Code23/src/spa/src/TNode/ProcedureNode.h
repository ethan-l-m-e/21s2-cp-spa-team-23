//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_PROCEDURENODE_H
#define SPA_PROCEDURENODE_H

#include "StmtLstNode.h"
#include "ProcNameNode.h"

class ProcedureNode: public StmtLstNode {
    ProcNameNode *procName;
    StatementList stmtLst;
public:
    ProcedureNode(ProcNameNode *procName, StatementList stmtLst);
    ProcName getProcName();
};

#endif //SPA_PROCEDURENODE_H
