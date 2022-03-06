//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_PROGRAMNODE_H
#define SPA_PROGRAMNODE_H

#include "Node.h"
#include "ProcedureNode.h"

typedef std::vector<ProcedureNode*> ProcedureList;

class ProgramNode: public Node {
    ProcedureList procLst;
public:
    ProgramNode(ProcedureList procLst);
    ProcedureList getProcLst();
};

#endif //SPA_PROGRAMNODE_H
