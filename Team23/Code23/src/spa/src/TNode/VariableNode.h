//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_VARIABLENODE_H
#define SPA_VARIABLENODE_H

#include "Node.h"

class VariableNode: public Node {
public:
    VariableNode(VarName name);
    VarName& getVariableName();
private:
    VarName varName;
};

#endif //SPA_VARIABLENODE_H
