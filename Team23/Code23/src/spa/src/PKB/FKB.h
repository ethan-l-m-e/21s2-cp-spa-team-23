#pragma once

#include<stdio.h>
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


class FKB {

private:
    FKB();

    static FKB *singleton;


public:

    static FKB *getInstance();

    void clearFKB();

    struct Entity {
        EntityTable<string> variables;
        EntityTable<string> procedures;
        EntityTable<string> constants;
    };

    Entity entity;

    struct Statement {
        StatementTable<StmtNode *> statements;
        StatementTable<AssignNode *> assignStatements;
        StatementTable<ReadNode *> readStatements;
        StatementTable<PrintNode *> printStatements;
        StatementTable<IfNode *> ifStatements;
        StatementTable<WhileNode *> whileStatements;
        StatementTable<CallNode *> callStatements;
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

    };

    Relationship relationship;


    OneToOneRelationship<int, NodeCFG *> stmtNumberToNodeCFGMap;






};