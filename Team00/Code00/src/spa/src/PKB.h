#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>

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

public:
//	static VarTable* varTable;
//	static int setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    // Setter Functions
    static static void addVariable(string variable);
    void addProcedures(string procedure);

    // Getter Functions

    unordered_set<string> getAllVariables();
    unordered_set<string> getAllProcedures();

//    void setFollows(int s1, int s2);
//    bool isFollows(int s1, int s2);

};