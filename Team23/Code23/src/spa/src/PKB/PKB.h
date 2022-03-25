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
        EntityTable<string> variables;
        EntityTable<string> procedures;
        EntityTable<string> constants;
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

        OneToOneRelationship<int, int> follows;

        ManyToManyRelationship<int, int> followsT;

        OneToManyRelationship<int, int> parent;

        ManyToManyRelationship<int, int> parentT;

        ManyToManyRelationship<int, string> usesS;
        ManyToManyRelationship<string, string> usesP;

        ManyToManyRelationship<int, string> modifiesS;
        ManyToManyRelationship<string, string> modifiesP;

        NextRelationship next;

    };

    Relationship relationship;








};