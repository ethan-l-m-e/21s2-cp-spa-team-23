//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_ASSIGNNODE_H
#define SPA_ASSIGNNODE_H

#include "StmtNode.h"
#include "VariableNode.h"
#include "BinaryOperatorNode.h"

class AssignNode: public StmtNode {
    VariableNode *leftNode;
    Expression rightNode;
public:
    explicit AssignNode(int num, VariableNode *leftNode, Expression rightNode);
    vector<VarName> getListOfVarUsed() override;
    vector<VarName> getListOfVarModified() override;
    vector<VarName> getAllVariables() override;
    vector<Constant> getAllConstants() override;
    VariableNode* getLeftNode() const;
    Expression getRightNode() const;
};

#endif //SPA_ASSIGNNODE_H
