//
// Created by Tin Hong Wen on 25/3/22.
//

#include "AffectsTOperator.h"

typedef std::unordered_set<string> variableSet, stmtSetStr;
typedef  std::string stmtStr, variable;
typedef  int statementNum;

bool AffectsTOperator::computeRelation(string left, string right) {
    if(!nextTOperator->computeRelation(left, right)) return false;
    if(affectsOperator->computeRelation(left, right)) {
        return true;
    } else {
        stmtSetStr left_new = affectsOperator->computeRHS(left);
        bool isRelation = false;
        for(stmtStr stmt: left_new) {
            isRelation = isRelation || affectsOperator->computeRelation(stmt, right);
        }
        return isRelation;
    }
}

stmtSetStr AffectsTOperator::computeLHS(string right) {
    auto computeFoo = [](string x)->stmtSetStr {
        return AffectsOperator::getInstance()->computeLHS(x);};
    return computeResultSetHelper(right, computeFoo);
}

stmtSetStr AffectsTOperator::computeRHS(string left) {
    auto computeFoo = [](string x)->stmtSetStr {
        return AffectsOperator::getInstance()->computeRHS(x);};
    return computeResultSetHelper(left, computeFoo);
}

stmtSetStr AffectsTOperator::computeResultSetHelper(string stmt,
                                              stmtSetStr (*computeDirection)(string)) {
    stmtSetStr resultSet;
    stmtSetStr adjStmts = computeDirection(stmt);

    for(stmtStr stmt: adjStmts) {
        stmtSetStr newResults = resultSetRecursionHelper(stmt, computeDirection);
        resultSet.insert(newResults.begin(), newResults.end());
    }
    return resultSet;
}

stmtSetStr AffectsTOperator::resultSetRecursionHelper(string stmt, stmtSetStr (*computeDirection)(string)) {
    stmtSetStr resultSet;
    resultSet.insert(stmt);
    stmtSetStr adjStatementList = computeDirection(stmt);

    for(stmtStr adjStmt: adjStatementList) {
        if(adjStmt != stmt) {
            stmtSetStr newResults = resultSetRecursionHelper(adjStmt, computeDirection);
            resultSet.insert(newResults.begin(), newResults.end());
        }
    }
    return resultSet;
}

AffectsTOperator *AffectsTOperator::singleton = nullptr;
AffectsTOperator::AffectsTOperator(): CacheOperator() {}
AffectsTOperator* AffectsTOperator::getInstance() {
    if (AffectsTOperator::singleton == nullptr) {
        AffectsTOperator::singleton = new AffectsTOperator();
    }
    return AffectsTOperator::singleton;
}