//
// Created by Tin Hong Wen on 4/2/22.
//

#ifndef SPA_RELATIONSHIPEXTRACTOR_H
#define SPA_RELATIONSHIPEXTRACTOR_H


#include "TNode/Node.h"
#include "TNode/StmtLstNode.h"

class RelationshipExtractor {
public:
    static void extractFollows(Node*);
    static void extractParent(Node*,vector<StmtLstNode*>);
    static vector<string> extractModifies(Node*);
    static vector<string> extractUses(Node*);
    static void detectDuplicateProcedure(Node*);
    static void extractRelationships(Node*);
};


#endif //SPA_RELATIONSHIPEXTRACTOR_H
