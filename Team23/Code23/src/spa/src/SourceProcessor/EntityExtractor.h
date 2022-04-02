//
// Created by Lucas Tai on 18/3/22.
//

#ifndef SPA_ENTITYEXTRACTOR_H
#define SPA_ENTITYEXTRACTOR_H
#include "TNode/TNode.h"

class EntityExtractor {
public:
    static void extractAllEntities(Node *node);

    static void assignProcedureToNodes(Node *node,ProcedureNode* proc);
};


#endif //SPA_ENTITYEXTRACTOR_H
