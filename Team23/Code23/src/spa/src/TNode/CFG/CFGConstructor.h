//
// Created by Lucas Tai on 12/3/22.
//

#ifndef SPA_CFGCONSTRUCTOR_H
#define SPA_CFGCONSTRUCTOR_H
#include "NodeCFG.h"
#include "TNode/ProcedureNode.h"

class CFGConstructor {

public:
    static NodeCFG* createCFG(ProcedureNode* p);
    static vector<NodeCFG*> populateCFG(Node* currNode, vector<NodeCFG*> prevNode);
};


#endif //SPA_CFGCONSTRUCTOR_H
