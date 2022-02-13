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

// Getter Functions (Variables, Procedures etc.)
unordered_set <string> PKB::getAllVariables() {
    return variablesSet;
}
unordered_set<string> PKB::getAllProcedures() {
    return proceduresSet;
}

// Setter Functions (Follows Relationship)

bool PKB::setFollows(int followee, int follower) {

}

// Getter Functions (Follows Relationship)

bool PKB::setFollows(int followee, int follower) {
    followeeToFollowerMap.emplace(followee, follower);
    followerToFolloweeMap.emplace(follower, followee);
}

bool PKB::isFollows(int followee, int follower) {
    if (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) {
        return followsMap[followee] == follower;
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
