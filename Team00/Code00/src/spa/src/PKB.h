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

class VarTable;  // no need to #include "VarTable.h" as all I need is postringer

class PKB {

private:
    PKB();

    static PKB* singleton;

    unordered_set<int> statementsSet;
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

    unordered_map<int, unordered_set<int>> tFolloweeToFollowerMap;
    unordered_map<int, unordered_set<int>> tFollowerToFolloweeMap;

    unordered_map<int, unordered_set<int>> parentToChildrenMap;
    unordered_map<int, int> childToParentMap;

    unordered_map<int, unordered_set<int>> tParentToChildrenMap;
    unordered_map<int, unordered_set<int>> tChildToParentMap;

public:
//	static VarTable* varTable;
//	static string setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    // Setter Functions (Variables, Procedures etc.)
    void addStatement(int statement);
    void addVariable(string variable);
    void addProcedure(string procedure);
    void addConstant(string constant);

    // Getter Functions (Variables, Procedures etc.)

    bool isStatement(int statement);
    bool isStatement(string statement);

    bool isVariable(string variable);
    bool isProcedure(string procedure);
    bool isConstant(string constant);

    unordered_set<string> getAllStatements();
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

    bool isAssignStatement(string statement);
    bool isReadStatement(string statement);
    bool isPrintStatement(string statement);
    bool isIfStatement(string statement);
    bool isWhileStatement(string statement);



    unordered_set<string> getAllAssignStatements();
    unordered_set<string> getAllReadStatements();
    unordered_set<string> getAllPrintStatements();
    unordered_set<string> getAllIfStatements();
    unordered_set<string> getAllWhileStatements();

    // Setter Functions (Follows Relationship)

    void setFollows(int followee, int follower);

    // Getter Functions (Follows Relationship)

    bool isFollows(int followee, int follower);
    unordered_set<int> getFollower(int followee);
    unordered_set<int> getFollowee(int follower);

    bool isFollows(string followee, string follower);
    unordered_set<string> getFollower(string followee);
    unordered_set<string> getFollowee(string follower);

    // Setter Functions (FollowsT Relationship)

    void setFollowsT(int followee, int follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(int followee, int follower);
    unordered_set<int> getFollowerT(int followee);
    unordered_set<int> getFolloweeT(int follower);

    bool isFollowsT(string followee, string follower);
    unordered_set<string> getFollowerT(string followee);
    unordered_set<string> getFolloweeT(string follower);


    // Setter Functions (Parent Relationship)

    void setParent(int parent, int child);

    // Getter Functions (Parent Relationship)

    bool isParent(int parent, int child);
    unordered_set<int> getChildren(int parent);
    unordered_set<int> getParent(int child);

    bool isParent(string parent, string child);
    unordered_set<string> getChildren(string parent);
    unordered_set<string> getParent(string child);


    // Setter Functions (ParentT Relationship)

    void setParentT(int parent, int child);

    // Getter Functions (ParentT Relationship)

    bool isParentT(int parent, int child);
    unordered_set<int> getChildrenT(int parent);
    unordered_set<int> getParentT(int child);

    bool isParentT(string parent, string child);
    unordered_set<string> getChildrenT(string parent);
    unordered_set<string> getParentT(string child);

    // Getter Functions (Uses Relationship)

    void setUses(int statement, unordered_set<string> variables);

};