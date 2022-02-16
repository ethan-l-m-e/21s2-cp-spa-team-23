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

    unordered_set<string> variablesSet;
    unordered_set<string> proceduresSet;
    unordered_set<string> constantsSet;

    unordered_set<string> assignStatementsSet;
    unordered_set<string> readStatementsSet;
    unordered_set<string> prstringStatementsSet;
    unordered_set<string> ifStatementsSet;
    unordered_set<string> whileStatementsSet;

    unordered_map<string, string> followeeToFollowerMap;
    unordered_map<string, string> followerToFolloweeMap;

    unordered_map<string, string> tFolloweeToFollowerMap;
    unordered_map<string, string> tFollowerToFolloweeMap;

    unordered_map<string, unordered_set<string>> parentToChildrenMap;
    unordered_map<string, string> childToParentMap;

public:
//	static VarTable* varTable;
//	static string setProcToAST(PROC p, TNode* r);
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

    void addAssignStatement(string statement);

    void addReadStatement(string statement);
    void addPrstringStatement(string statement);

    void addIfStatement(string statement);
    void addWhileStatement(string statement);

    // Getter Functions (Statement Types)

    bool isAssignStatement(string statement);
    bool isReadStatement(string statement);
    bool isPrstringStatement(string statement);
    bool isIfStatement(string statement);
    bool isWhileStatement(string statement);

    unordered_set<string> getAllAssignStatements();
    unordered_set<string> getAllReadStatements();
    unordered_set<string> getAllPrstringStatements();
    unordered_set<string> getAllIfStatements();
    unordered_set<string> getAllWhileStatements();

    // Setter Functions (Follows Relationship)

    void setFollows(string followee, string follower);

    // Getter Functions (Follows Relationship)

    bool isFollows(string followee, string follower);
    string getFollower(string followee);
    string getFollowee(string follower);

    // Setter Functions (FollowsT Relationship)

    void setFollowsT(string followee, string follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(string followee, string follower);
    string getFollowerT(string followee);
    string getFolloweeT(string follower);


    // Setter Functions (Parent Relationship)

    void setParent(string parent, string child);

    // Getter Functions (Parent Relationship)

    bool isParent(string parent, string child);
    unordered_set<string> getChildren(string parent);
    string getParent(string child);




};