//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_STMTLSTNODE_H
#define SPA_STMTLSTNODE_H

#include "Node.h"
#include "StmtNode.h"

class StmtLstNode: public StmtNode {
    StatementList stmtLst;
public:
    StmtLstNode(int num, StatementList stmtLst);
    vector<Node *> getStmtLst() override;
    //vector<VarName> getListOfVarUsed() override;
    //vector<VarName> getListOfVarModified() override;

    bool hasStmtLst() override;
};


#endif //SPA_STMTLSTNODE_H
