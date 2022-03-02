//
// Created by リム・イーサン on 2/3/22.
//

#include "ConstValueNode.h"

ConstValueNode::ConstValueNode(const string num) { this -> constValue = num; }
string ConstValueNode::getConstValue() {return this ->constValue; }
