//
// Created by Tin Hong Wen on 4/2/22.
//

#ifndef SPA_RELATIONSHIPEXTRACTOR_H
#define SPA_RELATIONSHIPEXTRACTOR_H


#include "TNode.h"

class RelationshipExtractor {
public:
    static void extractFollows(Node*);
    static void extractParents(Node*);
    static vector<string> extractModifies(Node*);
    static vector<string> extractUses(Node*);
    static void extractRelationships(Node*);
};


#endif //SPA_RELATIONSHIPEXTRACTOR_H
