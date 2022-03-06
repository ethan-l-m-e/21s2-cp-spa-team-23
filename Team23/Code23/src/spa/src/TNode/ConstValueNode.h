//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_CONSTVALUENODE_H
#define SPA_CONSTVALUENODE_H

#include "Node.h"

class ConstValueNode: public Node {
public:
    ConstValueNode(const string num);
    string getConstValue();
private:
    string constValue;
};

#endif //SPA_CONSTVALUENODE_H
