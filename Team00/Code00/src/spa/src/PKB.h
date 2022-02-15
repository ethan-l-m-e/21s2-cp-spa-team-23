#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {

private:
    PKB();

    static PKB* singleton;

    unordered_set<string> variablesSet;
    unordered_set<string> proceduresSet;
    unordered_set<string> constantsSet;

    unordered_set<int> assignStatementsSet;
    unordered_set<int> readStatementsSet;
    unordered_set<int> printStatementsSet;
    unordered_set<int> ifStatementsSet;
    unordered_set<int> whileStatementsSet;

    unordered_map<int, int> followeeToFollowerMap;
    unordered_map<int, int> followerToFolloweeMap;

    unordered_map<int, int> tFolloweeToFollowerMap;
    unordered_map<int, int> tFollowerToFolloweeMap;

    unordered_map<int, unordered_set<int>> parentToChildrenMap;
    unordered_map<int, int> childToParentMap;

public:
//	static VarTable* varTable;
//	static int setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    // Setter Functions (Variables, Procedures etc.)
    void addVariable(string variable);
    void addProcedure(string procedure);
    void addConstant(string constant);

    // Getter Functions (Variables, Procedures etc.)

    bool isVariable(string variable);
    bool isProcedure(string procedure);
    bool isConstant(string constant);

    unordered_set<string> getAllVariables();
    unordered_set<string> getAllProcedures();
    unordered_set<string> getAllConstants();

    // Setter Functions (Statement Types)

    void addAssignStatement(int statement);

    void addReadStatement(int statement);
    void addPrintStatement(int statement);

    void addIfStatement(int statement);
    void addWhileStatement(int statement);

    // Getter Functions (Statement Types)

    bool isAssignStatement(int statement);
    bool isReadStatement(int statement);
    bool isPrintStatement(int statement);
    bool isIfStatement(int statement);
    bool isWhileStatement(int statement);

    unordered_set<int> getAllAssignStatements();
    unordered_set<int> getAllReadStatements();
    unordered_set<int> getAllPrintStatements();
    unordered_set<int> getAllIfStatements();
    unordered_set<int> getAllWhileStatements();

    // Setter Functions (Follows Relationship)

    void setFollows(int followee, int follower);

    // Getter Functions (Follows Relationship)

    bool isFollows(int followee, int follower);
    int getFollower(int followee);
    int getFollowee(int follower);

    // Setter Functions (FollowsT Relationship)

    void setFollowsT(int followee, int follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(int followee, int follower);
    int getFollowerT(int followee);
    int getFolloweeT(int follower);


    // Setter Functions (Parent Relationship)

    void setParent(int parent, int child);

    // Getter Functions (Parent Relationship)

    bool isParent(int parent, int child);
    unordered_set<int> getChildren(int parent);
    int getParent(int child);


};