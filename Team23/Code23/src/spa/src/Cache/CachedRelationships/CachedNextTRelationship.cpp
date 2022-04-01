//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedNextTRelationship.h"

bool CachedNextTRelationship::isRelationship(string lhs, string rhs) {
    bool boolResults;
    /*checks if result (returning true) exist or query is in history*/
    if(pairHistory.isInHistory(lhs, rhs) || CachedManyToManyRelationship::isRelationship(lhs, rhs)) {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = CachedManyToManyRelationship::isRelationship(lhs, rhs);
    } else {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = nextTOp->computeRelation(lhs, rhs);
        if (boolResults) CachedManyToManyRelationship::setRelationship(lhs, rhs);
    }
    return boolResults;
}

unordered_set<string> CachedNextTRelationship::getRHS(string lhs) {
    unordered_set<string> results;
    if(getRhsHistory.isInHistory(lhs) || CachedManyToManyRelationship::getRHS(lhs).size() > 0) {
        getRhsHistory.addToHistory(lhs);
        results = CachedManyToManyRelationship::getRHS(lhs);
    } else {
        getRhsHistory.addToHistory(lhs);

        unordered_set<string> allStmtNo = getAllStmtInSameProcedureAs(lhs);
        for(string right: allStmtNo){   // for all numbers in the procedure
            bool notInResults =  results.find(right) == results.end();
            bool isRS = false;
            if(notInResults && isRelationship(lhs, right)) {
                results.insert(right);
                isRS = true;
            }
            if(getRhsHistory.isInHistory(right) && isRS) {
                unordered_set<string> resultsFromRight = getRHS(right);
                results.insert(resultsFromRight.begin(), resultsFromRight.end());
            }
        }

        //results = nextTOp->computeRHS(lhs);
        //CachedManyToManyRelationship::setRelationship(lhs, results);
    }
    return results;
}

unordered_set<string> CachedNextTRelationship::getLHS(string rhs) {
    unordered_set<string> results;
    if(getLhsHistory.isInHistory(rhs) || CachedManyToManyRelationship::getLHS(rhs).size() > 0) {
        getLhsHistory.addToHistory(rhs);
        results = CachedManyToManyRelationship::getLHS(rhs);
    } else {
        getLhsHistory.addToHistory(rhs);

        unordered_set<string> allStmtNo = getAllStmtInSameProcedureAs(rhs);
        for(string left: allStmtNo){
            bool notInResults =  results.find(left) == results.end();
            bool isRS = false;
            if(notInResults && isRelationship(left, rhs)) {
                results.insert(left);
                isRS = true;
            }
            if(getLhsHistory.isInHistory(left) && isRS) {
                unordered_set<string> resultsFromLeft = getLHS(left);
                results.insert(resultsFromLeft.begin(), resultsFromLeft.end());
            }
        }
        //results = nextTOp->computeLHS(rhs);
        //CachedManyToManyRelationship::setRelationship(results, rhs);
    }

    //unordered_set<string> defaultReturn = CachedManyToManyRelationship::getLHS(rhs);
    return results;
}
CachedNextTRelationship *CachedNextTRelationship::singleton = nullptr;
CachedNextTRelationship *CachedNextTRelationship::getInstance() {
    if (CachedNextTRelationship::singleton == nullptr) {
        CachedNextTRelationship::singleton = new CachedNextTRelationship;
    }
    return CachedNextTRelationship::singleton;
}
