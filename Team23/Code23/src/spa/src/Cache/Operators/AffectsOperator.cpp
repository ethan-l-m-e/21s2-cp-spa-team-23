//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsOperator.h"
#include "NextTOperator.h"

using namespace std;


typedef std::unordered_set<string> variableSet, stmtSetStr;
typedef  std::string stmtStr, variable;
typedef  int statementNum;

static stmtSetStr blackListStatements = {};
static stmtSetStr whiteListStatements = {};


bool AffectsOperator::computeRelation(string left, string right) {
    //step 0: check if left are right are both assign statements
    if(!(isAssignStmt(left) && isAssignStmt(right))) return false;

    // step 1: see if same procedure, might need PKB to implement this (technically can use nextOp* but this is for further optimisation

    // step 2: check if var mod and uses
    string modifiedVar = *(getVarModifiedBy(left).begin());
    auto usedVar = getVarUsedBy(right);
    bool varInUses = false;
    for(string var: usedVar) {
        if (modifiedVar == var) {
            varInUses = true;
        }
    }

    // step 3: finds execution path
    if(varInUses) {
        setBlacklist(pkb->relationship.modifiesS.getLHS(modifiedVar));
        NodeCFG* leftNode = retrieveNode(left);
        NodeCFG* rightNode = retrieveNode(right);
        int size = getSize();
        return graphMethods->DFSBoolean(leftNode,
                                        rightNode,
                                        size,
                                        IsReachableForward
                                        );
    } else {
        return false;
    }
}


unordered_set<string> AffectsOperator::computeLHS(string right) {
    stmtSetStr lhsSet = NextTOperator::getInstance()->computeLHS(right);
    stmtSetStr  resultSet;
    for(stmtStr left: lhsSet) {
        if(computeRelation(left, right)) {
            resultSet.insert(left);
        }
    }
    return resultSet;
}

stmtSetStr AffectsOperator::computeRHS(string left) {
    stmtSetStr rhsSet = NextTOperator::getInstance()->computeRHS(left);
    stmtSetStr  resultSet;
    for(stmtStr right: rhsSet) {
        if(computeRelation(left, right)) {
            resultSet.insert(right);
        }
    }
    return resultSet;
}

bool AffectsOperator::IsReachableForward(NodeCFG* srcNode,
                                         NodeCFG* destNode,
                                         unordered_map<int, bool> &visited,
                                         vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    if(srcVal == destVal) return true;
    if(isInBlackList(srcVal)) return false;

    visited[srcVal] = true;
    path.push_back(srcVal);

    unordered_set<NodeCFG*> adjNodes = graphMethods->collateAllAdjacentNodes(srcNode);
    unordered_set<NodeCFG*>::iterator adj;
    for(adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        // if not visited, perform recursion again
        int adjStmtNo = adjacentNode->getStatementNumber();
        if (!visited[adjStmtNo]) {
            if (IsReachableForward(adjacentNode, destNode, visited, path))
                return true;
        }
    }

    path.pop_back();
    return false;
}


unordered_set<int> AffectsOperator::DFSResultSetRecursion(NodeCFG* currentNode,
                                                          unordered_map<int, bool> &visited,
                                                          unordered_set<int> resultSet,
                                                          unordered_set<NodeCFG *> (*getAdjFoo)(NodeCFG *)) {
    int currVal = currentNode->getStatementNumber();

    /**
     * perform isRelation to ensure correctness
     *
     *
     * check if is an obstacle or a lookout for LHS direction with map?
     * Say, you got multiple whiteList values and a single blackList value
     * if hit blackList value, the var for that whiteListed value becomes inaccessible for that portion
     */

    if(isInWhiteList(currVal))
        return {currVal};

    if(isInBlackList(currVal))
        return {};

    visited[currVal] = true;
    unordered_set<NodeCFG *> adjNodes = getAdjFoo(currentNode);

    unordered_set<NodeCFG *>::iterator adj;
    for (adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;
        int adjStmtNo = adjacentNode->getStatementNumber();
        if(!visited[adjStmtNo]) {
                unordered_set<int> resultSetInAdjacentNode = DFSResultSetRecursion(adjacentNode, visited, resultSet,getAdjFoo);
                resultSet.insert(resultSetInAdjacentNode.begin(), resultSetInAdjacentNode.end());

        }
    }
    return resultSet;
}

unordered_set<string> AffectsOperator::removeContainerFromSet(unordered_set<string> &stmtSet) {
    unordered_set<string> outputSet = {};
    unordered_set<string>::iterator i;
    for(i = stmtSet.begin(); i != stmtSet.end(); i++) {
        string stmtNo = *i;
        // also remove print and call that uses but not modify
        if(!isContainerStatement(stmtNo))
            outputSet.insert(stmtNo);
    }
    return outputSet;
}


bool AffectsOperator::isContainerStatement(string stmtNo) {
    bool isWhile = pkb->statement.whileStatements.isStatementNumber(stmtNo);
    bool isIf = pkb->statement.ifStatements.isStatementNumber(stmtNo);
    return isWhile || isIf;
}
bool AffectsOperator::isAssignStmt(string stmtNo) {return pkb->statement.assignStatements.isStatementNumber(stmtNo);}
stmtSetStr AffectsOperator::getStmtModifying(string var) {return pkb->relationship.modifiesS.getLHS(var);}
stmtSetStr AffectsOperator::getStmtUsing(string var) {return pkb->relationship.usesS.getLHS(var);}

variableSet AffectsOperator::getVarModifiedBy(string stmt) {return pkb->relationship.modifiesS.getRHS(stmt);}
variableSet AffectsOperator::getVarUsedBy(string stmt) {return pkb->relationship.usesS.getRHS(stmt);}

bool AffectsOperator::isInBlackList(int stmtNo) {
    if(blackListStatements.find(to_string(stmtNo)) != blackListStatements.end()) {
        return true;
    }
    else return false;
}

bool AffectsOperator::isInWhiteList(int stmtNo) {
    if(whiteListStatements.find(to_string(stmtNo)) != whiteListStatements.end()) {
        return true;
    }
    else return false;
}

void AffectsOperator::setBlacklist(unordered_set<string> newSet) {
    blackListStatements.clear();
    blackListStatements = removeContainerFromSet(newSet);
}

void AffectsOperator::setWhiteList(unordered_set<string> newSet) {
    whiteListStatements.clear();
    whiteListStatements = removeContainerFromSet(newSet);
}

AffectsOperator *AffectsOperator::singleton = nullptr;
AffectsOperator::AffectsOperator(): CacheOperator() {}
AffectsOperator* AffectsOperator::getInstance() {
    if (AffectsOperator::singleton == nullptr) {
        AffectsOperator::singleton = new AffectsOperator();
    }
    return AffectsOperator::singleton;
}

/*
stmtSetStr AffectsOperator::findResultSet(string stmt,
                                          variableSet variables,
                                          pair<stmtSetStr, stmtSetStr>(*blackAndWhiteListFoo)(string),
                                          unordered_set<NodeCFG*>(*getAdjFoo)(NodeCFG*),
                                          stmtSetNum (*dfsRecursionFoo)(NodeCFG*,
                                                                        unordered_map<int, bool>&,
                                                                        unordered_set<int>)) {
    if(!isAssignStmt(stmt)) return {};
    unordered_set<string> listOfAllObstacles;
    unordered_set<string> listOfAllLookouts;


    for(string var: variables) {
        auto blackAndWhite = blackAndWhiteListFoo(var);
        listOfAllObstacles.insert(blackAndWhite.first.begin(), blackAndWhite.first.end());
        listOfAllLookouts.insert(blackAndWhite.second.begin(), blackAndWhite.second.end());
    }

    setBlacklist(listOfAllObstacles);
    setWhiteList(listOfAllLookouts);

    NodeCFG* node = retrieveNode(stmt);
    int size = getSize();
    unordered_set<int> resultSet = graphMethods->DFSResultSet(
            node,
            size,
            getAdjFoo,
            dfsRecursionFoo
    );

    return convertIntToString(resultSet);
}

unordered_set<int> AffectsOperator::searchForAffectsBefore(NodeCFG* rightNode,
                                                           unordered_map<int, bool> &visited,
                                                           unordered_set<int> nextSet) {
    return DFSResultSetRecursion(rightNode, visited, nextSet,
                                 graphMethods->collateAllPreviousNodes);
}

unordered_set<int> AffectsOperator::searchForAffectsAfter(NodeCFG* leftNode,
                                                          unordered_map<int, bool> &visited,
                                                          unordered_set<int> nextSet) {
    return DFSResultSetRecursion(leftNode, visited, nextSet,
                                 graphMethods->collateAllAdjacentNodes);
}
*/