//
// Created by リム・イーサン on 5/3/22.
//

#ifndef SPA_CALLNODE_H
#define SPA_CALLNODE_H

#include "StmtNode.h"
#include "ProcNameNode.h"
#include "ProgramNode.h"

class CallNode : public StmtNode {
    ProcNameNode *procNameNode;
    ProcedureList getProcLst();
public:
    CallNode(int num, ProcNameNode *procNameNode);
    [[nodiscard]] ProcName getProcName() const;
    Node* getProcedure();
};


#endif //SPA_CALLNODE_H
