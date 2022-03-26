//
// Created by Tin Hong Wen on 4/2/22.
//

#ifndef SPA_RELATIONSHIPEXTRACTOR_H
#define SPA_RELATIONSHIPEXTRACTOR_H

#include <string>
#include <vector>
#include <unordered_set>

#include "TNode/TNode.h"
#include "TNode/StmtLstNode.h"

using namespace std;

class RelationshipExtractor {
public:
    static void extractFollows(Node*);
    static void extractParent(Node*,vector<StmtLstNode*>);
    static vector<string> extractModifies(Node*);
    static vector<string> extractUses(Node*);
    static void createCFGAndExtractNext(Node*);
    static void extractRelationships(Node*);

    static void extractCalls(Node *node, vector<ProcedureNode *> parentList, ProcedureNode* latestProc);
};


#endif //SPA_RELATIONSHIPEXTRACTOR_H
