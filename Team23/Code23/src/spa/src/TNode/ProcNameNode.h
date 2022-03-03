//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_PROCNAMENODE_H
#define SPA_PROCNAMENODE_H

#include "Node.h"

class ProcNameNode: public Node {
public:
    ProcNameNode(ProcName name);
    ProcName getProcedureName();
private:
    ProcName procedureName;
};

#endif //SPA_PROCNAMENODE_H
