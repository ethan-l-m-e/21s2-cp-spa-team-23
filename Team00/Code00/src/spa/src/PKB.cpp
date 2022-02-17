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

// Setter Functions (Assign Nodes)

void PKB::addAssignNode(AssignNode *assignNode) {
    assignNodesSet.insert(assignNode);
}

// Getter Functions (Assign Nodes)

vector<AssignNode *> PKB::getAllAssignNodes() {

    vector<AssignNode *> assignNodesVector;

    assignNodesVector.insert(assignNodesVector.end(), assignNodesSet.begin(), assignNodesSet.end());

    return assignNodesVector;
}

unordered_set<string> convertSetIntegersToSetStrings(unordered_set<int> setIntegers) {

    unordered_set<string> setStrings;

    for (int i : setIntegers) {
        setStrings.insert(std::to_string(i));
    }

    return setStrings;
}

// Setter Functions (Variables, Procedures etc.)

void PKB::addStatement(int statement) {
    statementsSet.insert(statement);
}

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

bool PKB::isStatement(int statement) {
    return statementsSet.find(statement) != statementsSet.end();
}
bool PKB::isStatement(string statement) {
    return isStatement(std::stoi(statement));
}


bool PKB::isVariable(string variable) {
    return variablesSet.find(variable) != variablesSet.end();
}
bool PKB::isProcedure(string procedure) {
    return proceduresSet.find(procedure) != proceduresSet.end();
}
bool PKB::isConstant(string constant) {
    return proceduresSet.find(constant) != proceduresSet.end();
}

unordered_set<string> PKB::getAllStatements() {
    return convertSetIntegersToSetStrings(statementsSet);
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

void PKB::addAssignStatement(int statement) {
    addStatement(statement);
    assignStatementsSet.insert(statement);
}

void PKB::addReadStatement(int statement) {
    addStatement(statement);
    readStatementsSet.insert(statement);
}
void PKB::addPrintStatement(int statement) {
    addStatement(statement);
    printStatementsSet.insert(statement);
}
void PKB::addIfStatement(int statement) {
    addStatement(statement);
    ifStatementsSet.insert(statement);
}
void PKB::addWhileStatement(int statement) {
    addStatement(statement);
    whileStatementsSet.insert(statement);
}


// Getter Functions (Statement Types)

bool PKB::isAssignStatement(int statement) {
    return assignStatementsSet.find(statement) != readStatementsSet.end();
}
bool PKB::isAssignStatement(string statement) {
    return isAssignStatement(std::stoi(statement));
}
bool PKB::isReadStatement(int statement) {
    return readStatementsSet.find(statement) != readStatementsSet.end();
}
bool PKB::isReadStatement(string statement) {
    return isReadStatement(std::stoi(statement));
}
bool PKB::isPrintStatement(int statement) {
    return printStatementsSet.find(statement) != printStatementsSet.end();
}
bool PKB::isPrintStatement(string statement) {
    return isPrintStatement(std::stoi(statement));
}
bool PKB::isIfStatement(int statement) {
    return ifStatementsSet.find(statement) != ifStatementsSet.end();
}
bool PKB::isIfStatement(string statement) {
    return isIfStatement(std::stoi(statement));
}
bool PKB::isWhileStatement(int statement) {
    return whileStatementsSet.find(statement) != whileStatementsSet.end();
}
bool PKB::isWhileStatement(string statement) {
    return isWhileStatement(std::stoi(statement));
}



unordered_set<string> PKB::getAllAssignStatements() {
    return convertSetIntegersToSetStrings(assignStatementsSet);
}
unordered_set<string> PKB::getAllReadStatements() {
    return convertSetIntegersToSetStrings(readStatementsSet);
}
unordered_set<string> PKB::getAllPrintStatements() {
    return convertSetIntegersToSetStrings(printStatementsSet);
}
unordered_set<string> PKB::getAllIfStatements() {
    return convertSetIntegersToSetStrings(ifStatementsSet);
}
unordered_set<string> PKB::getAllWhileStatements() {
    return convertSetIntegersToSetStrings(whileStatementsSet);
}


// Setter Functions (Follows Relationship)

void PKB::setFollows(int followee, int follower) {
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
bool PKB::isFollows(string followee, string follower) {
    return isFollows(std::stoi(followee), std::stoi(follower));
}



unordered_set<int> PKB::getFollower(int followee) {

    unordered_set<int> emptySet;

    return (followeeToFollowerMap.find(followee) != followeeToFollowerMap.end()) ? unordered_set<int>{followeeToFollowerMap[followee]} : emptySet;
}

unordered_set<string> PKB::getFollower(string followee) {
    return convertSetIntegersToSetStrings(getFollower(std::stoi(followee)));
}

unordered_set<int> PKB::getFollowee(int follower) {

    unordered_set<int> emptySet;

    return (followerToFolloweeMap.find(follower) != followerToFolloweeMap.end()) ? unordered_set<int>{followerToFolloweeMap[follower]} : emptySet;
}
unordered_set<string> PKB::getFollowee(string follower) {
    return convertSetIntegersToSetStrings(getFollowee(std::stoi(follower)));
}


// Setter Functions (FollowsT Relationship)

void PKB::setFollowsT(int followee, int follower) {

    if (tFolloweeToFollowerMap.find(followee) == tFolloweeToFollowerMap.end()) {
        tFolloweeToFollowerMap.emplace(followee, unordered_set<int>{follower});
    } else {
        tFolloweeToFollowerMap[followee].insert(follower);
    }

    if (tFollowerToFolloweeMap.find(follower) == tFollowerToFolloweeMap.end()) {
        tFollowerToFolloweeMap.emplace(follower, unordered_set<int>{followee});
    } else {
        tFollowerToFolloweeMap[follower].insert(followee);
    }
}

// Getter Functions (FollowsT Relationship)

bool PKB::isFollowsT(int followee, int follower) {
    if (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) {
        return tFolloweeToFollowerMap[followee].find(follower) != tFolloweeToFollowerMap[followee].end();
    } else {
        return false;
    }
}
bool PKB::isFollowsT(string followee, string follower) {
    return isFollowsT(std::stoi(followee), std::stoi(follower));
}

unordered_set<int> PKB::getFollowerT(int followee) {

    unordered_set<int> emptySet;

    return (tFolloweeToFollowerMap.find(followee) != tFolloweeToFollowerMap.end()) ? tFolloweeToFollowerMap[followee] : emptySet;
}
unordered_set<string> PKB::getFollowerT(string followee) {
    return convertSetIntegersToSetStrings(getFollowerT(std::stoi(followee)));
}

unordered_set<int> PKB::getFolloweeT(int follower) {

    unordered_set<int> emptySet;

    return (tFollowerToFolloweeMap.find(follower) != tFollowerToFolloweeMap.end()) ? tFollowerToFolloweeMap[follower] : emptySet;
}
unordered_set<string> PKB::getFolloweeT(string follower) {
    return convertSetIntegersToSetStrings(getFolloweeT(std::stoi(follower)));
}

// Setter Functions (Parent Relationship)

void PKB::setParent(int parent, int child) {

    childToParentMap.emplace(child, parent);

    if (parentToChildrenMap.find(parent) == parentToChildrenMap.end()) {
        parentToChildrenMap.emplace(parent, unordered_set<int>{child});
    } else {
        parentToChildrenMap[parent].insert(child);
    }

}

// Getter Functions (Parent Relationship)

bool PKB::isParent(int parent, int child) {
    if (childToParentMap.find(child) != childToParentMap.end()) {
        return childToParentMap[child] != parent;
    } else {
        return false;
    }
}
bool PKB::isParent(string parent, string child) {
    return isParent(std::stoi(parent), std::stoi(child));
}


unordered_set<int> PKB::getChildren(int parent) {

    unordered_set<int> emptySet;

    return (parentToChildrenMap.find(parent) != parentToChildrenMap.end()) ? parentToChildrenMap[parent] : emptySet;
}
unordered_set<string> PKB::getChildren(string parent) {
    return convertSetIntegersToSetStrings(getChildren(std::stoi(parent)));
}

unordered_set<int> PKB::getParent(int child) {

    unordered_set<int> emptySet;

    return (childToParentMap.find(child) != childToParentMap.end()) ? unordered_set<int>{childToParentMap[child]} : emptySet;
}
unordered_set<string> PKB::getParent(string child) {
    return convertSetIntegersToSetStrings(getParent(std::stoi(child)));
}


// Setter Functions (ParentT Relationship)

void PKB::setParentT(int parent, int child) {

    if (tParentToChildrenMap.find(parent) == tParentToChildrenMap.end()) {
        tParentToChildrenMap.emplace(parent, unordered_set<int>{child});
    } else {
        tParentToChildrenMap[parent].insert(child);
    }

    if (tChildToParentMap.find(child) == tChildToParentMap.end()) {
        tChildToParentMap.emplace(child, unordered_set<int>{parent});
    } else {
        tChildToParentMap[child].insert(parent);
    }
}

// Getter Functions (ParentT Relationship)

bool PKB::isParentT(int parent, int child) {
    if (tChildToParentMap.find(child) != tChildToParentMap.end()) {
        return tChildToParentMap[child].find(parent) != tChildToParentMap[child].end();
    } else {
        return false;
    }
}
bool PKB::isParentT(string parent, string child) {
    return isParent(std::stoi(parent), std::stoi(child));
}

unordered_set<int> PKB::getChildrenT(int parent) {

    unordered_set<int> emptySet;

    return (tParentToChildrenMap.find(parent) != tParentToChildrenMap.end()) ? tParentToChildrenMap[parent] : emptySet;

}
unordered_set<string> PKB::getChildrenT(string parent) {
    return convertSetIntegersToSetStrings(getChildrenT(std::stoi(parent)));
}

unordered_set<int> PKB::getParentT(int child) {

    unordered_set<int> emptySet;

    return (tChildToParentMap.find(child) != tChildToParentMap.end()) ? tChildToParentMap[child] : emptySet;
}
unordered_set<string> PKB::getParentT(string child) {
    return convertSetIntegersToSetStrings(getParentT(std::stoi(child)));
}


// Setter Functions (Uses Relationship)

void PKB::setUses(int statement, unordered_set<string> variables) {
    statementToVariablesUsedMap[statement] = variables;

    for (string v : variables) {
        if (variableUsedToStatementMap.find(v) == variableUsedToStatementMap.end()) {
            variableUsedToStatementMap.emplace(v, unordered_set<int>{statement});
        } else {
            variableUsedToStatementMap[v].insert(statement);
        }
    }


}

// Getter Functions (Uses Relationship)

bool PKB::isUses(int statement, string variable) {
    if (statementToVariablesUsedMap.find(statement) != statementToVariablesUsedMap.end()) {
        return statementToVariablesUsedMap[statement].find(variable) != statementToVariablesUsedMap[statement].end();
    } else {
        return false;
    }
}
bool PKB::isUses(string statement, string variable) {
    return isUses(std::stoi(statement), variable);
}

unordered_set<string> PKB::getVariablesUsed(int statement) {

    unordered_set<string> emptySet;

    return (statementToVariablesUsedMap.find(statement) != statementToVariablesUsedMap.end()) ? statementToVariablesUsedMap[statement] : emptySet;
}

unordered_set<string> PKB::getVariablesUsed(string statement) {
    return getVariablesUsed(std::stoi(statement));
}

unordered_set<string> PKB::getUserStatements(string variable) {

    unordered_set<int> emptySet;
    unordered_set<int> statementsSet = (variableUsedToStatementMap.find(variable) != variableUsedToStatementMap.end()) ? variableUsedToStatementMap[variable] : emptySet;

    return convertSetIntegersToSetStrings(statementsSet);
}

// Setter Functions (Modifies Relationship)

void PKB::setModifies(int statement, unordered_set<string> variables) {
    statementToVariablesModifiedMap[statement] = variables;

    for (string v : variables) {
        if (variableModifiedToStatementMap.find(v) == variableModifiedToStatementMap.end()) {
            variableModifiedToStatementMap.emplace(v, unordered_set<int>{statement});
        } else {
            variableModifiedToStatementMap[v].insert(statement);
        }
    }
}

// Getter Functions (Modifies Relationship)

bool PKB::isModifies(int statement, string variable) {
    if (statementToVariablesModifiedMap.find(statement) != statementToVariablesModifiedMap.end()) {
        return statementToVariablesModifiedMap[statement].find(variable) != statementToVariablesModifiedMap[statement].end();
    } else {
        return false;
    }
}

bool PKB::isModifies(string statement, string variable) {
    return isModifies(std::stoi(statement), variable);
}

unordered_set<string> PKB::getVariablesModified(int statement) {
    unordered_set<string> emptySet;

    return (statementToVariablesModifiedMap.find(statement) != statementToVariablesModifiedMap.end()) ? statementToVariablesModifiedMap[statement] : emptySet;
}

unordered_set<string> PKB::getVariablesModified(string statement) {
    return getVariablesModified(std::stoi(statement));
}

unordered_set<string> PKB::getModifierStatements(string variable) {
    unordered_set<int> emptySet;
    unordered_set<int> statementsSet = (variableModifiedToStatementMap.find(variable) != variableModifiedToStatementMap.end()) ? variableModifiedToStatementMap[variable] : emptySet;

    return convertSetIntegersToSetStrings(statementsSet);
}
