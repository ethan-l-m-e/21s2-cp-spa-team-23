//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsTRelationship.h"

static CachedAffectsRelationship* affects = CachedAffectsRelationship::getInstance();

bool CachedAffectsTRelationship::isRelationship(string lhs, string rhs) {
    if(lhs == "1" && rhs == "10")
        cout << "";
    bool boolResults;
    //checks if result (returning true) exist or if query is inside history
    if(pairHistory.isInHistory(lhs, rhs) || CachedManyToManyRelationship::isRelationship(lhs, rhs)) {
        printStmt("retrieving Affects* isRelationship "  + lhs + " " + rhs + " from storage\n");
        pairHistory.addToHistory(lhs, rhs);
        boolResults = CachedManyToManyRelationship::isRelationship(lhs, rhs);
    } else {
        printStmt("computing Affects* isRelationship " + lhs + " " + rhs + "\n");
        pairHistory.addToHistory(lhs, rhs);
        //boolResults = affectsTOp->computeRelation(lhs, rhs);
        boolResults = computeRelation(lhs, rhs);

        if (boolResults) CachedManyToManyRelationship::setRelationship(lhs, rhs);
    }
    return boolResults;
}


bool CachedAffectsTRelationship::computeRelation(string left, string right) {
    unordered_set<string> left_new = affects->getRHS(left);
    unordered_set<string> visitedList = {};
    for(string leftAdj: left_new) {
        if(computeRelationRec(left, right, visitedList)) return true;
    }
    return false;
}

bool CachedAffectsTRelationship::computeRelationRec(string left, string right, unordered_set<string> visitedList) {
    if(!nextT->isRelationship(left, right)) return false;
    if(affects->isRelationship(left, right)) return true;
    else {
        visitedList.insert(left);
        unordered_set<string> left_new = affects->getRHS(left);
        for(string leftAdj: left_new) {
            if((visitedList.find(leftAdj) == visitedList.end()) &&
               computeRelationRec(leftAdj, right, visitedList))
                return true;
        }
        return false;
    }
}


unordered_set<string> CachedAffectsTRelationship::getRHS(string lhs) {
    unordered_set<string> results;
    if(getRhsHistory.isInHistory(lhs)) {
        printStmt("retrieving Affects* getRHS"  + lhs + " from storage\n");
        getRhsHistory.addToHistory(lhs);
        results = CachedManyToManyRelationship::getRHS(lhs);
    } else {
        printStmt("computing Affects* getRHS " + lhs + "\n");
        getRhsHistory.addToHistory(lhs);
        unordered_set<string> allStmtNo = getAllStmtInSameProcedureAs(lhs);
        for(string right: allStmtNo){
            bool notInResults =  results.find(right) == results.end();
            bool isRelation = false;

            if(!notInResults)
                printStmt(lhs + " is inside results, skipping computation! \n");
            if(notInResults && isRelationship(lhs, right)) {
                results.insert(right);
                isRelation = true;
            }
            if(getRhsHistory.isInHistory(right) && isRelation) {
                printStmt(right + " has been called previously, fetching results from " + right + "\n");
                unordered_set<string> resultsFromRight = getRHS(right);
                results.insert(resultsFromRight.begin(), resultsFromRight.end());
            }
        }
    }
    return results;
}

unordered_set<string> CachedAffectsTRelationship::getLHS(string rhs) {
    unordered_set<string> results;
    if(getLhsHistory.isInHistory(rhs)) {
        printStmt("retrieving Affects* getLHS"  + rhs + " from storage\n");
        getLhsHistory.addToHistory(rhs);
        results = CachedManyToManyRelationship::getLHS(rhs);
    } else {
        printStmt("computing Affects* getLHS " + rhs + "\n");
        getLhsHistory.addToHistory(rhs);
        unordered_set<string> allStmtNo = getAllStmtInSameProcedureAs(rhs);
        for(string left: allStmtNo){
            bool notInResults =  results.find(left) == results.end();
            bool isRelation = false;

            if(!notInResults)
                printStmt(left + " is inside results, skipping computation! \n");

            if(notInResults && isRelationship(left, rhs)) {
                results.insert(left);
                isRelation = true;
            }
            if(getLhsHistory.isInHistory(left) && isRelation) {
                printStmt(left + " has been called previously, fetching results from " + left + "\n");
                unordered_set<string> resultsFromLeft = getLHS(left);
                results.insert(resultsFromLeft.begin(), resultsFromLeft.end());
            }
        }
    }
    return results;
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