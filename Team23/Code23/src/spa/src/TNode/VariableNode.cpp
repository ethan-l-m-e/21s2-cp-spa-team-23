//
// Created by リム・イーサン on 2/3/22.
//

#include "VariableNode.h"

VariableNode::VariableNode(VarName name) { this ->varName = std::move(name); }
VarName &VariableNode::getVariableName(){ return this ->varName; }
