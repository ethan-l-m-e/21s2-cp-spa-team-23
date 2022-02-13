#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"


//int PKB::setProcToAST(PROC p, TNode* r) {
//	return 0;
//}
//TNode* PKB::getRootAST (PROC p){
//	return nullptr;
//}

PKB *PKB::singleton = nullptr;

PKB::PKB() {

}

PKB* PKB::getInstance() {

    if (PKB::singleton == nullptr) {
        PKB::singleton = new PKB();
    }

    return PKB::singleton;

}


// Setter Functions (Variables, Procedures etc.)
void PKB::addVariable(string variable) {
    variablesSet.insert(variable);
}
void PKB::addProcedures(string procedure) {
    proceduresSet.insert(procedure);
}

void PKB::addConstant(string constant) {
    constantsSet.insert(constant);
}


void addReadStatement(int statement) {
    readStatementsSet.insert(statement);
}
void addPrintStatement(int statement) {
    printStatementsSet.insert(statement);
}

// Getter Functions (Variables, Procedures etc.)
unordered_set <string> PKB::getAllVariables() {
    return variablesSet;
}
unordered_set<string> PKB::getAllProcedures() {
    return proceduresSet;
}

unordered_set<string> PKB::getAllConstants() {
    return constantsSet;
}

// Setter Functions (Follows Relationship)

bool PKB::setFollows(int followee, int follower) {
    followeeToFollowerMap.emplace(followee, follower);
    followerToFolloweeMap.emplace(follower, followee);
}

// Getter Functions (Follows Relationship)

bool PKB::isFollows(int followee, int follower) {
    if (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) {
        return followeeToFollowerMap[followee] == follower;
    } else {
        return false;
    }
}

int PKB::getFollower(int followee) {
    return (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) ? followeeToFollowerMap[followee] : -1;
}

int PKB::getFollowee(int follower) {
    return (followerToFolloweeMap.find(follower) != followerToFolloweeMap.end()) ? followerToFolloweeMap[follower] : -1;
}


// Setter Functions (FollowsT Relationship)

bool PKB::setFollows(int followee, int follower) {
    tFolloweeToFollowerMap.emplace(followee, follower);
    tFollowerToFolloweeMap.emplace(follower, followee);
}

// Getter Functions (FollowsT Relationship)

bool PKB::isFollows(int followee, int follower) {
    if (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) {
        return tFolloweeToFollowerMap[followee] == follower;
    } else {
        return false;
    }
}

int PKB::getFollowerT(int followee) {
    return (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) ? tFolloweeToFollowerMap[followee] : -1;
}

int PKB::getFollowee(int follower) {
    return (tFollowerToFolloweeMap.find(follower) != tFollowerToFolloweeMap.end()) ? tFollowerToFolloweeMap[follower] : -1;
}


// Setter Functions (Parent Relationship)

bool PKB::setParent(int parent, int child) {

    childToParentMap.emplace(child, parent);

    if (parentToChildrenMap.find(parent) == parentToChildrenMap.end()) {
        parentToChildrenMap.emplace(parent, unordered_set<int>{child});
    } else {
        parentToChildrenMap[parent].insert(child)
    }

}

// Getter Functions (Parent Relationship)

bool PKB::isParent(int parent, int child) {
    if (childToParentMap.find(child) != childToParentMap.end()) {
        return childToParentMap[child] == parent;
    } else {
        return false;
    }
}

int PKB::getChildren(int parent) {
    return (parentToChildrenMap.find(parent) != parentToChildrenMap.end()) ? parentToChildrenMap[parent] : unordered_set<int>;
}

int PKB::getParent(int child) {
    return (childToParentMap.find(child) != childToParentMap.end()) ? childToParentMap[child] : -1;
}
