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
    stmtSetStr resultSet;
    stmtSetStr left_new = affectsOperator->computeLHS(right);
    resultSet.insert(left_new.begin(), left_new.end());
    for(stmtStr stmt: left_new) {
        stmtSetStr newResults = computeLHS(stmt);
        resultSet.insert(newResults.begin(), newResults.end());
    }
    return resultSet;
}

stmtSetStr AffectsTOperator::computeRHS(string left) {
    stmtSetStr resultSet;
    stmtSetStr right_new = affectsOperator->computeRHS(left);
    resultSet.insert(right_new.begin(), right_new.end());
    for(stmtStr stmt: right_new) {
        stmtSetStr newResults = computeRHS(stmt);
        resultSet.insert(newResults.begin(), newResults.end());
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