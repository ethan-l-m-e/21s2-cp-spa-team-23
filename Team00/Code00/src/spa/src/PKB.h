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

    unordered_map<int, int> followeeToFollowerMap;
    unordered_map<int, int> followerToFolloweeMap;

public:
//	static VarTable* varTable;
//	static int setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    // Setter Functions (Variables, Procedures etc.)
    void addVariable(string variable);
    void addProcedures(string procedure);

    // Getter Functions (Variables, Procedures etc.)

    unordered_set<string> getAllVariables();
    unordered_set<string> getAllProcedures();

    // Setter Functions (Follows Relationship)

    void setFollows(int followee, int follower);

    // Getter Functions (Follows Relationship)

    bool isFollows(int followee, int follower);
    int getFollower(int followee);
    int getFollowee(int follower);


};