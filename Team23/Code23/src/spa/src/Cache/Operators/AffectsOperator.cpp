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

    // step 1: see if same procedure, might need PKB to implement this, although optional

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