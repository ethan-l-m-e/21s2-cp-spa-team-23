//
// Created by Karan Dev Sapra on 29/3/22.
//

#include "CachedManyToManyRelationship.h"
#include "PKB/PKB.h"

unordered_set<string> CachedManyToManyRelationship::getAllStmtInSameProcedureAs(string stmt) {
    return PKB::getInstance()->statement.statements.getAllStatementNumbers();
}

void CachedManyToManyRelationship::clear() {
    ManyToManyRelationship::clear();
    pairHistory.clear();
    getLhsHistory.clear();
    getRhsHistory.clear();
}

static bool print = false;


void CachedManyToManyRelationship::printStmt(string input) {
    if(print) {
        cout << input;
    }
}

void CachedManyToManyRelationship::printStmt(string input, bool in) {
    if(in) {
        cout << input;
    }
}

bool History::isInHistory(string key) {
    return historySingle.find(key) != historySingle.end();
}

bool History::isInHistory(string lhs, string rhs) {
    tuple<string, string> tup = make_tuple(lhs, rhs);
    return historyPair.find(tup) != historyPair.end();;
}

void History::addToHistory(string key) {
    historySingle.insert(key);
}

void History::addToHistory(string lhs, string rhs) {
    tuple<string, string> tup = make_tuple(lhs, rhs);
    historyPair.insert(tup);
}

void History::clear() {
    historySingle.clear();
    historyPair.clear();
}