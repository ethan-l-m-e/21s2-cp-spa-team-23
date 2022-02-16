#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"


//string PKB::setProcToAST(PROC p, TNode* r) {
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
void PKB::addProcedure(string procedure) {
    proceduresSet.insert(procedure);
}

void PKB::addConstant(string constant) {
    constantsSet.insert(constant);
}


// Getter Functions (Variables, Procedures etc.)

bool PKB::isVariable(string variable) {
    return variablesSet.find(variable) != variablesSet.end();
}
bool PKB::isProcedure(string procedure) {
    return proceduresSet.find(procedure) != proceduresSet.end();
}
bool PKB::isConstant(string constant) {
    return proceduresSet.find(constant) != proceduresSet.end();
}

unordered_set <string> PKB::getAllVariables() {
    return variablesSet;
}
unordered_set<string> PKB::getAllProcedures() {
    return proceduresSet;
}

unordered_set<string> PKB::getAllConstants() {
    return constantsSet;
}


// Setter Functions (Statement Types)

void PKB::addAssignStatement(string statement) {
    assignStatementsSet.insert(statement);
}

void PKB::addReadStatement(string statement) {
    readStatementsSet.insert(statement);
}
void PKB::addPrstringStatement(string statement) {
    prstringStatementsSet.insert(statement);
}
void PKB::addIfStatement(string statement) {
    ifStatementsSet.insert(statement);
}
void PKB::addWhileStatement(string statement) {
    whileStatementsSet.insert(statement);
}


// Getter Functions (Statement Types)

bool PKB::isAssignStatement(string statement) {
    return assignStatementsSet.find(statement) != readStatementsSet.end();
}

bool PKB::isReadStatement(string statement) {
    return readStatementsSet.find(statement) != readStatementsSet.end();
}

bool PKB::isPrstringStatement(string statement) {
    return prstringStatementsSet.find(statement) != prstringStatementsSet.end();
}
bool PKB::isIfStatement(string statement) {
    return ifStatementsSet.find(statement) != ifStatementsSet.end();
}
bool PKB::isWhileStatement(string statement) {
    return whileStatementsSet.find(statement) != whileStatementsSet.end();
}

unordered_set<string> PKB::getAllAssignStatements() {
    return assignStatementsSet;
}
unordered_set<string> PKB::getAllReadStatements() {
    return readStatementsSet;
}
unordered_set<string> PKB::getAllPrstringStatements() {
    return prstringStatementsSet;
}
unordered_set<string> PKB::getAllIfStatements() {
    return ifStatementsSet;
}
unordered_set<string> PKB::getAllWhileStatements() {
    return whileStatementsSet;
}


// Setter Functions (Follows Relationship)

void PKB::setFollows(string followee, string follower) {
    followeeToFollowerMap.emplace(followee, follower);
    followerToFolloweeMap.emplace(follower, followee);
}

// Getter Functions (Follows Relationship)

bool PKB::isFollows(string followee, string follower) {
    if (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) {
        return followeeToFollowerMap[followee] == follower;
    } else {
        return false;
    }
}

string PKB::getFollower(string followee) {
    return (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) ? followeeToFollowerMap[followee] : -1;
}

string PKB::getFollowee(string follower) {
    return (followerToFolloweeMap.find(follower) != followerToFolloweeMap.end()) ? followerToFolloweeMap[follower] : -1;
}


// Setter Functions (FollowsT Relationship)

void PKB::setFollowsT(string followee, string follower) {
    tFolloweeToFollowerMap.emplace(followee, follower);
    tFollowerToFolloweeMap.emplace(follower, followee);
}

// Getter Functions (FollowsT Relationship)

bool PKB::isFollowsT(string followee, string follower) {
    if (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) {
        return tFolloweeToFollowerMap[followee] == follower;
    } else {
        return false;
    }
}

string PKB::getFollowerT(string followee) {
    return (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) ? tFolloweeToFollowerMap[followee] : -1;
}

string PKB::getFolloweeT(string follower) {
    return (tFollowerToFolloweeMap.find(follower) != tFollowerToFolloweeMap.end()) ? tFollowerToFolloweeMap[follower] : -1;
}


// Setter Functions (Parent Relationship)

void PKB::setParent(string parent, string child) {

    childToParentMap.emplace(child, parent);

    if (parentToChildrenMap.find(parent) == parentToChildrenMap.end()) {
        parentToChildrenMap.emplace(parent, unordered_set<string>{child});
    } else {
        parentToChildrenMap[parent].insert(child);
    }

}

// Getter Functions (Parent Relationship)

bool PKB::isParent(string parent, string child) {
    if (childToParentMap.find(child) != childToParentMap.end()) {
        return childToParentMap[child] == parent;
    } else {
        return false;
    }
}

unordered_set<string> PKB::getChildren(string parent) {

    unordered_set<string> emptySet;

    return (parentToChildrenMap.find(parent) != parentToChildrenMap.end()) ? parentToChildrenMap[parent] : emptySet;
}

string PKB::getParent(string child) {
    return (childToParentMap.find(child) != childToParentMap.end()) ? childToParentMap[child] : -1;
}

// Setter Functions (ParentT Relationship)

void setParentT(string parent, string child);