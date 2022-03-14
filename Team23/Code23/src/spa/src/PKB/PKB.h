#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "TNode/TNode.h"

#include "PKB/Statement/Statement.h"
#include "PKB/Entity/Entity.h"
#include "PKB/Relationship/Relationship.h"

using namespace std;
typedef short PROC;


class PKB {

private:
    PKB();

    static PKB *singleton;


public:

    static PKB *getInstance();

    void clearPKB();

    struct Entity {
        GenericEntity<string> variables;
        GenericEntity<string> procedures;
        GenericEntity<string> constants;
    };

    Entity entity;

    struct Statement {
        GenericStatement<StmtNode> statementClass;
        GenericSpecificStatement<AssignNode> assignStatementClass;
        GenericSpecificStatement<ReadNode> readStatementClass;
        GenericSpecificStatement<PrintNode> printStatementClass;
        GenericSpecificStatement<IfNode> ifStatementClass;
        GenericSpecificStatement<WhileNode> whileStatementClass;
    };

    Statement statement;

    struct Relationship {

        GenericRelationship<int, int> followsRelationshipClass;

        GenericTransitiveRelationship<int, int> tFollowsRelationshipClass;

        GenericRelationship<int, int> parentRelationshipClass;

        GenericTransitiveRelationship<int, int> tParentRelationshipClass;

        GenericRelationship<int, string> usesSRelationshipClass;
        GenericRelationship<string, string> usesPRelationshipClass;

        GenericTransitiveRelationship<int, string> tUsesSRelationshipClass;

        GenericTransitiveRelationship<int, string> tUsesPRelationshipClass;

        GenericRelationship<int, string> modifiesSRelationshipClass;
        GenericRelationship<string, string> modifiesPRelationshipClass;

        GenericTransitiveRelationship<int, string> tModifiesSRelationshipClass;

        GenericTransitiveRelationship<int, string> tModifiesPRelationshipClass;

    };

    Relationship relationship;






};