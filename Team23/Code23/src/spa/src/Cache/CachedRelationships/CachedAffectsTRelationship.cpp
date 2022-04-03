//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsTRelationship.h"

static CachedAffectsRelationship* affects = CachedAffectsRelationship::getInstance();

bool CachedAffectsTRelationship::isRelationship(string lhs, string rhs) {
    bool boolResults;
    //checks if result (returning true) exist or if query is inside history
    if(pairHistory.isInHistory(lhs, rhs) || CachedManyToManyRelationship::isRelationship(lhs, rhs)) {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = CachedManyToManyRelationship::isRelationship(lhs, rhs);
    } else {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = affectsTOp->computeRelation(lhs, rhs);
        if (boolResults) CachedManyToManyRelationship::setRelationship(lhs, rhs);
    }
    return boolResults;
}

unordered_set<string> CachedAffectsTRelationship::getRHS(string lhs) {
    unordered_set<string> results;
    if(getRhsHistory.isInHistory(lhs)) {
        getRhsHistory.addToHistory(lhs);
        results = CachedManyToManyRelationship::getRHS(lhs);
    } else {
        getRhsHistory.addToHistory(lhs);
        std::function computeFoo = [&lhs](string x)->unordered_set<string> {return affects->getRHS(lhs);};
        results = computeResultSetHelper(lhs, computeFoo);
        CachedManyToManyRelationship::setRelationship(lhs, results);
    }
    return results;
}

unordered_set<string> CachedAffectsTRelationship::getLHS(string rhs) {
    unordered_set<string> results;
    if(getLhsHistory.isInHistory(rhs)) {
        results = CachedManyToManyRelationship::getLHS(rhs);
    } else {
        getLhsHistory.addToHistory(rhs);
        std::function computeFoo = [&rhs](string x)->unordered_set<string> {return affects->getLHS(rhs);};
        results = computeResultSetHelper(rhs, computeFoo);
        CachedManyToManyRelationship::setRelationship(rhs, results);
    }
    return results;
}

bool CachedAffectsTRelationship::computeRelation(string left, string right) {
    if(!nextT->isRelationship(left, right)) return false;
    if(affects->isRelationship(left, right)) return true;
    else {
        unordered_set<string> affected = affects->getRHS(left);
        for(string stmt: affected) {
            if(affects->isRelationship(stmt, right)) return true;
        }
        return false;
    }
}

unordered_set<string> CachedAffectsTRelationship::computeResultSetHelper(string stmt,
                                                                         std::function<unordered_set<string>(string)>
                                                                                 computeDirection) {
    unordered_set<string> resultSet;
    unordered_set<string> adjStmts = computeDirection(stmt);

    for(string stmt: adjStmts) {
        unordered_set<string> newResults = resultSetRecursionHelper(stmt, computeDirection);
        resultSet.insert(newResults.begin(), newResults.end());
    }
    return resultSet;
}

unordered_set<string> CachedAffectsTRelationship::resultSetRecursionHelper(string stmt,
                                                                           std::function<unordered_set<string>(string)>
                                                                                   computeDirection) {
    unordered_set<string> resultSet;
    resultSet.insert(stmt);
    unordered_set<string> adjStatementList = computeDirection(stmt);

    for(string adjStmt: adjStatementList) {
        if(adjStmt != stmt) {
            unordered_set<string> newResults = resultSetRecursionHelper(adjStmt, computeDirection);
            resultSet.insert(newResults.begin(), newResults.end());
        }
    }
    return resultSet;
}