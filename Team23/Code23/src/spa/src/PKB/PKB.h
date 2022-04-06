#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "TNode/TNode.h"
#include "TNode/CFG/NodeCFG.h"

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
        EntityTable variables;
        EntityTable procedures;
        EntityTable constants;
    };

    // All the different kinds of entities (i.e variables, procedures and constants) are all stored in an `Entity` struct named `entity`
    Entity entity;

    struct Statement {
        StatementTable<StmtNode *> statements;
        StatementTable<AssignNode *> assignStatements;
        StatementTableWithVariableMap<ReadNode *> readStatements;
        StatementTableWithVariableMap<PrintNode *> printStatements;
        StatementTable<IfNode *> ifStatements;
        StatementTable<WhileNode *> whileStatements;
        StatementTableWithProcedureMap<CallNode *> callStatements;

    };

    // All the different kinds of statements (i.e normal statements, assign statements, read statements etc.) are all stored in a `Statement` struct named `statement`
    Statement statement;

    struct Relationship {

        // Since each statement can be followed by at most one statement in the Follows Relationship, a Relationship Table of type `OneToOneRelationship` is used
        OneToOneRelationship follows;

        // Since each statement can be followed by zero or more statements in the FollowsT Relationship, a Relationship Table of type `ManyToManyRelationship` is used
        ManyToManyRelationshipWithMinMax followsT;

        // Since a parent can have multiple children but a child can only have a single parent in the Parent Relationship, a Relationship Table of type `OneToManyRelationship` is used
        OneToManyRelationship parent;

        ManyToManyRelationship parentT;

        ManyToManyRelationship usesS;
        ManyToManyRelationship usesP;

        ManyToManyRelationship modifiesS;
        ManyToManyRelationship modifiesP;

        ManyToManyRelationship calls;
        ManyToManyRelationship callsT;

        NextRelationship next;

    };

    // All the different kinds of relationships (i.e Follows, FollowsT, Parent etc.) are all stored in a `Relationship` struct named `relationship`
    Relationship relationship;








};
