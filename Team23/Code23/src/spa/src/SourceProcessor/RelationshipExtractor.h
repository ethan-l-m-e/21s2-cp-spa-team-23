//
// Created by Tin Hong Wen on 4/2/22.
//

#ifndef SPA_RELATIONSHIPEXTRACTOR_H
#define SPA_RELATIONSHIPEXTRACTOR_H


#include "TNode/Node.h"
#include "TNode/ProcedureNode.h"
#include "TNode/StmtLstNode.h"

class RelationshipExtractor {
public:
    static void extractFollows(Node*);
    static void extractParent(Node*,vector<StmtLstNode*>);
    static vector<string> extractModifies(Node*);
    static vector<string> extractUses(Node*);
    static void extractRelationships(Node*);

    static void extractCalls(Node *node, vector<StmtLstNode *> parentList, ProcedureNode currProcName);
};


#endif //SPA_RELATIONSHIPEXTRACTOR_H
