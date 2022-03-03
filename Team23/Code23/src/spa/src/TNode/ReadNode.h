//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_READNODE_H
#define SPA_READNODE_H

#include "StmtNode.h"
#include "VariableNode.h"

// Definition:
// read: 'read' var_name';'
class ReadNode: public StmtNode {
    VariableNode *varNode;
public:
    ReadNode(int num, VariableNode* varNode);
    [[nodiscard]] VarName getVarName() const;
    vector<VarName> getListOfVarModified() override;
};

#endif //SPA_READNODE_H
