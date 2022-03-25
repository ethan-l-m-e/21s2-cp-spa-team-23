//
// Created by Tin Hong Wen on 22/3/22.
//

#include "CacheOperator.h"

bool CacheOperator::findRelation(string left, string right) {return false;}
unordered_set<string> CacheOperator::findLHS(string rightNode) {return {};}
unordered_set<string> CacheOperator::findRHS(string leftNode) {return {};}

static GraphMethods* graphMethods = GraphMethods::getInstance();
PKB* CacheOperator::pkb = PKB::getInstance();

NodeCFG* CacheOperator::retrieveNode(string stmtNo) {
    return pkb->relationship.next.getCFGNode(stmtNo);
}

bool CacheOperator::stmtIsNotInSource(vector<string> argList) {
    for(string stmtNo: argList) {
        if(!pkb->statement.statements.isStatementNumber(stmtNo)) {
            cout << "stmtNo: " << stmtNo << "not in source;\n";
            return true;
        }
    }
    return false;
}
int CacheOperator::getSize() {
    return pkb->relationship.next.getCFGSize();
}

unordered_set<string> CacheOperator::convertIntToString(unordered_set<int> intSet) {
    unordered_set<string> stringSet = {};
    unordered_set<int>::iterator i;
    for(i = intSet.begin(); i!= intSet.end(); ++i) {
        stringSet.insert(to_string(*i));
    }
    return stringSet;
}