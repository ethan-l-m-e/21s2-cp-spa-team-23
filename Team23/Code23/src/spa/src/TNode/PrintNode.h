//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_PRINTNODE_H
#define SPA_PRINTNODE_H

#include "StmtNode.h"
#include "VariableNode.h"

// Definition:
// print: 'print' var_name';'
class PrintNode: public StmtNode {
    VariableNode *varNode;
public:
    PrintNode(int num, VariableNode* varNode);
    [[nodiscard]] VarName getVarName() const;
    vector<VarName> getListOfVarUsed() override;
};

#endif //SPA_PRINTNODE_H
