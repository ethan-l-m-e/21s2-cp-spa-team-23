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

    unordered_set<string> statementsSet;
    unordered_set<string> variablesSet;
    unordered_set<string> proceduresSet;
    unordered_set<string> constantsSet;

    unordered_set<string> assignStatementsSet;
    unordered_set<string> readStatementsSet;
    unordered_set<string> printStatementsSet;
    unordered_set<string> ifStatementsSet;
    unordered_set<string> whileStatementsSet;

    unordered_map<string, string> followeeToFollowerMap;
    unordered_map<string, string> followerToFolloweeMap;

    unordered_map<string, unordered_set<string>> tFolloweeToFollowerMap;
    unordered_map<string, unordered_set<string>> tFollowerToFolloweeMap;

    unordered_map<string, unordered_set<string>> parentToChildrenMap;
    unordered_map<string, string> childToParentMap;

    unordered_map<string, unordered_set<string>> tParentToChildrenMap;
    unordered_map<string, unordered_set<string>> tChildToParentMap;

public:
//	static VarTable* varTable;
//	static string setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    // Setter Functions (Variables, Procedures etc.)
    void addStatement(string statement);
    void addVariable(string variable);
    void addProcedure(string procedure);
    void addConstant(string constant);

    // Getter Functions (Variables, Procedures etc.)

    bool isStatement(string statement);
    bool isVariable(string variable);
    bool isProcedure(string procedure);
    bool isConstant(string constant);

    unordered_set<string> getAllStatements();
    unordered_set<string> getAllVariables();
    unordered_set<string> getAllProcedures();
    unordered_set<string> getAllConstants();

    // Setter Functions (Statement Types)

    void addAssignStatement(string statement);

    void addReadStatement(string statement);
    void addPrintStatement(string statement);

    void addIfStatement(string statement);
    void addWhileStatement(string statement);

    // Getter Functions (Statement Types)

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

    void setFollows(string followee, string follower);

    // Getter Functions (Follows Relationship)

    bool isFollows(string followee, string follower);
    unordered_set<string> getFollower(string followee);
    unordered_set<string> getFollowee(string follower);

    // Setter Functions (FollowsT Relationship)

    void setFollowsT(string followee, string follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(string followee, string follower);
    unordered_set<string> getFollowerT(string followee);
    unordered_set<string> getFolloweeT(string follower);


    // Setter Functions (Parent Relationship)

    void setParent(string parent, string child);

    // Getter Functions (Parent Relationship)

    bool isParent(string parent, string child);
    unordered_set<string> getChildren(string parent);
    unordered_set<string> getParent(string child);

    // Setter Functions (ParentT Relationship)

    void setParentT(string parent, string child);

    // Getter Functions (ParentT Relationship)

    bool isParentT(string parent, string child);
    unordered_set<string> getChildrenT(string parent);
    unordered_set<string> getParentT(string child);


};