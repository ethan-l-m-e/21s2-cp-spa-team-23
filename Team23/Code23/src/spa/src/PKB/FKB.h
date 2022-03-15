#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "TNode/TNode.h"
//#include "TNode/CFG/NodeCFG.h"

#include "PKB/Statement/Statement.h"
#include "PKB/Entity/Entity.h"
#include "PKB/Relationship/Relationship.h"

using namespace std;
typedef short PROC;


class FKB {

private:
    FKB();

    static FKB *singleton;


public:

    static FKB *getInstance();

    void clearFKB();

    struct Entity {
        GenericEntity<string> variables;
        GenericEntity<string> procedures;
        GenericEntity<string> constants;
    };

    Entity entity;

    struct Statement {
        StatementTable<StmtNode *> statementClass;
        StatementTable<AssignNode *> assignStatementClass;
        StatementTable<ReadNode *> readStatementClass;
        StatementTable<PrintNode *> printStatementClass;
        StatementTable<IfNode *> ifStatementClass;
        StatementTable<WhileNode *> whileStatementClass;
        StatementTable<CallNode *> callStatementClass;
    };

    Statement statement;

    struct Relationship {

        OneToOneRelationship<int, int> followsRelationshipClass;

        ManyToManyRelationship<int, int> tFollowsRelationshipClass;

        OneToManyRelationship<int, int> parentRelationshipClass;

        ManyToManyRelationship<int, int> tParentRelationshipClass;

        ManyToManyRelationship<int, string> usesSRelationshipClass;
        ManyToManyRelationship<string, string> usesPRelationshipClass;

        ManyToManyRelationship<int, string> modifiesSRelationshipClass;
        ManyToManyRelationship<string, string> modifiesPRelationshipClass;


    };

    Relationship relationship;






};