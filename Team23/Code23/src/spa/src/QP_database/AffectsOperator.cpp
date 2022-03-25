//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsOperator.h"

using namespace std;


typedef std::unordered_set<string> variableSet, stmtSetStr;
typedef  std::string stmtStr, variable;
typedef  int statementNum;

static stmtSetStr blackListStatements = {};
static stmtSetStr whiteListStatements = {};


bool AffectsOperator::isInBlackList(int stmtNo) {
    if(blackListStatements.find(to_string(stmtNo)) != blackListStatements.end()) {
        cout << stmtNo << "is in blackList\n";
        return true;
    }
    else return false;
}

bool AffectsOperator::isInWhiteList(int stmtNo) {
    if(whiteListStatements.find(to_string(stmtNo)) != whiteListStatements.end()) {
        cout << stmtNo << "is in whiteList\n";
        return true;
    }
    else return false;
}


bool AffectsOperator::findRelation(string left, string right) {
    //step 0: check if left are right are both assign statements
    if(!(isAssignStmt(left) && isAssignStmt(right))) return false;

    // step 1: see if same procedure, might need PKB to implement this (technically can use nextOp* but this is for optimisation

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


unordered_set<string> AffectsOperator::findLHS(string right) {
    auto blackAndWhiteFoo = [](variable var)->pair<stmtSetStr, stmtSetStr> {
        stmtSetStr black;
        stmtSetStr white;
        stmtSetStr allModifyingVar = getStmtModifying(var);
        for(stmtStr x: allModifyingVar) {
            if(pkb->statement.assignStatements.isStatementNumber(x)) {
                white.insert(x);
            } else {
                black.insert(x);
            }
        }
        return pair<stmtSetStr, stmtSetStr>{black, white};
    };

    return findResultSet(right,
                         getVarUsedBy(right),
                         blackAndWhiteFoo,
                         graphMethods->collateAllPreviousNodes,
                         searchForAffectsBefore);

     /*if(!isAssignStmt(right)) return {};
    auto usedVar = getVarUsedBy(right);
    unordered_set<string> allStmtModifyingVar;
    for(string var: usedVar) {
        // get all stmt that modifies this var
        unordered_set<string> newSet = getStmtModifying(var);
        allStmtModifyingVar.insert(newSet.begin(), newSet.end());
    }

    setBlacklist(allStmtModifyingVar);
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    unordered_set<int> resultSet = graphMethods->DFSResultSet(
            rightNode,
            size,
            graphMethods->collateAllPreviousNodes,
            searchForAffectsBefore
            );

    return convertIntToString(resultSet);*/
}

stmtSetStr AffectsOperator::findRHS(string left) {
    auto blackAndWhiteFoo = [](variable var)->pair<stmtSetStr, stmtSetStr> {
        stmtSetStr black = getStmtModifying(var);
        stmtSetStr white;
        stmtSetStr allUsingVar = getStmtUsing(var);
        for(stmtStr x: allUsingVar) {
            if(pkb->statement.assignStatements.isStatementNumber(x))
                white.insert(x);
        }
        return pair<stmtSetStr, stmtSetStr>{black, white};
    };
    return findResultSet(left,
                         getVarModifiedBy(left),
                         blackAndWhiteFoo,
                         graphMethods->collateAllAdjacentNodes,
                         searchForAffectsAfter);

}

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

bool AffectsOperator::IsReachableForward(NodeCFG* srcNode,
                                         NodeCFG* destNode,
                                         unordered_map<int, bool> &visited,
                                         vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    if(srcVal == destVal) {
        return true;
    }
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
    // for find LHS
    if(isInBlackList(currVal))
        return {};
    if(isInWhiteList(currVal))
        return {currVal};

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

// called obstacle list as it "trips" affects
void AffectsOperator::setBlacklist(unordered_set<string> newSet) {
    blackListStatements.clear();
    blackListStatements = removeContainerFromSet(newSet);
}

void AffectsOperator::setWhiteList(unordered_set<string> newSet) {
    whiteListStatements.clear();
    whiteListStatements = removeContainerFromSet(newSet);
}



bool AffectsOperator::isContainerStatement(string stmtNo) {
    bool isWhile = pkb->statement.whileStatements.isStatementNumber(stmtNo);
    bool isIf = pkb->statement.ifStatements.isStatementNumber(stmtNo);
    return isWhile || isIf;
}
bool AffectsOperator::isAssignStmt(string stmtNo) {return pkb->statement.assignStatements.isStatementNumber(stmtNo);}
stmtSetStr AffectsOperator::getStmtModifying(string var) {return pkb->relationship.modifiesS.getLHS(var);}
stmtSetStr AffectsOperator::getStmtUsing(string var) {return pkb->relationship.usesS.getLHS(var);}

//stmtSetStr AffectsOperator::collectBlackAndWhiteList(string var) {

//}

/*
 * blackList: blocks further traversal
 * whiteList: blocks traversal and add result list
 *
 *
 * findLHS:
 *      blackList:
 *          calls modifies var
 *          read modifies var
 *      whiteList:
 *          assign modifies var
 *
 * findRHS:
 *      blackList:
 *          calls modifies var
 *          read modifies var
 *          assign modifies var
 *      whiteList:
 *          assign uses var
 */

variableSet AffectsOperator::getVarModifiedBy(string stmt) {return pkb->relationship.modifiesS.getRHS(stmt);}
variableSet AffectsOperator::getVarUsedBy(string stmt) {return pkb->relationship.usesS.getRHS(stmt);}


AffectsOperator *AffectsOperator::singleton = nullptr;
AffectsOperator::AffectsOperator(): CacheOperator() {}
AffectsOperator* AffectsOperator::getInstance() {
    if (AffectsOperator::singleton == nullptr) {
        AffectsOperator::singleton = new AffectsOperator();
    }
    return AffectsOperator::singleton;
}