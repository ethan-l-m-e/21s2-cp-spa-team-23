//
// Created by Tin Hong Wen on 4/2/22.
//

#ifndef SPA_RELATIONSHIPEXTRACTOR_H
#define SPA_RELATIONSHIPEXTRACTOR_H


#include "TNode.h"

class RelationshipExtractor {
public:
    static void extractFollows(TNode*);
    static void extractParents(TNode*);
    static vector<string> extractModifies(TNode*);
    static vector<string> extractUses(TNode*);
    static void extractRelationships(TNode*);
};


#endif //SPA_RELATIONSHIPEXTRACTOR_H
