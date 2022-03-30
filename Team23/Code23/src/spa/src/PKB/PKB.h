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

    Entity entity;

    struct Statement {
        StatementTable<StmtNode *> statements;
        StatementTable<AssignNode *> assignStatements;
        ReadStatementTable readStatements;
        PrintStatementTable printStatements;
        StatementTable<IfNode *> ifStatements;
        StatementTable<WhileNode *> whileStatements;
        CallStatementTable callStatements;
    };

    Statement statement;

    struct Relationship {

        OneToOneRelationship follows;

        ManyToManyRelationship followsT;

        OneToManyRelationship parent;

        ManyToManyRelationship parentT;

        ManyToManyRelationship usesS;
        ManyToManyRelationship usesP;

        ManyToManyRelationship modifiesS;
        ManyToManyRelationship modifiesP;

        ManyToManyRelationship<string, string> calls;
        ManyToManyRelationship<string, string> callsT;

        NextRelationship next;

    };

    Relationship relationship;








};
