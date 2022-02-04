#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

typedef int STMT_NO;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);


    // Setter Functions
    void setFollows(STMT_NO s1, STMT_NO s2);

    // Getter Functions
    bool isFollows(STMT_NO s1, STMT_NO s2);

};