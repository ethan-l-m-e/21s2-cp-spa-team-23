//
// Created by Lucas Tai on 12/3/22.
//

#ifndef SPA_CFGCONSTRUCTOR_H
#define SPA_CFGCONSTRUCTOR_H
#include "TNode/ProcedureNode.h"
#include "PKB.h"
#include "NodeCFG.h"

class CFGConstructor {

public:
    static vector<NodeCFG*>* createCFG(ProcedureNode p);
    static vector<NodeCFG*>* populateCFG(Node* currNode, vector<NodeCFG*>* prevNode);
};


#endif //SPA_CFGCONSTRUCTOR_H
