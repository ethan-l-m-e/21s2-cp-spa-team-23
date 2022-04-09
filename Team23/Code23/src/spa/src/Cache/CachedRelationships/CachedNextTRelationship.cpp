//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedNextTRelationship.h"




// runtime: O(h), where h < n. + caching -> O(1)
bool CachedNextTRelationship::isRelationship(string lhs, string rhs) {
    bool boolResults;
    /*checks if result (returning true) exist or query is in history*/
    if(pairHistory.isInHistory(lhs, rhs) || CachedManyToManyRelationship::isRelationship(lhs, rhs)) {
        printStmt("retrieving NextT isRelationship "  + lhs + " " + rhs + " from storage\n");
        pairHistory.addToHistory(lhs, rhs);
        boolResults = CachedManyToManyRelationship::isRelationship(lhs, rhs);
    } else {
        printStmt("computing NextT isRelationship " + lhs + " " + rhs + "\n");
        pairHistory.addToHistory(lhs, rhs);
        boolResults = nextTOp->computeRelation(lhs, rhs);
        if (boolResults) {
            CachedManyToManyRelationship::setRelationship(lhs, rhs);
        }
    }
    return boolResults;
}

// previous ver runtime: O(n). consistently
unordered_set<string> CachedNextTRelationship::getRHS(string lhs) {
    unordered_set<string> results;
    //Taking from cache. O(n) -> O(1)
    if(getRhsHistory.isInHistory(lhs)) {
        printStmt("retrieving NextT getRHS"  + lhs + " from storage\n");
        results = CachedManyToManyRelationship::getRHS(lhs);
    } else {
        // computing. runtime: O(n*h).
        // but with caching can shave off a lot of runtime if overloaded with optimizeQueryClauses -> O(h*n) -> O(n) -> O(1)
        printStmt("computing NextT RHS " + lhs + "\n");
        getRhsHistory.addToHistory(lhs);
        unordered_set<string> allStmtNo = getAllStmtInSameProcedureAs(lhs);
        for(string right: allStmtNo){
            bool notInResults =  results.find(right) == results.end();
            bool isRelation = false;

            if(!notInResults)
                printStmt(lhs + " is inside results, skipping computation! \n");

            //1) check if the string is inside the results. O(n)
            if(notInResults && isRelationship(lhs, right)) {
                results.insert(right);
                isRelation = true;
            }

            // 2) to skip computing RHS by simply taking results from right. next*(x, y) = next*(x, s) & next*(s, y). O(n) ~ O(1)
            if(getRhsHistory.isInHistory(right) && isRelation) {
                printStmt(right + " has been called previously, fetching results from " + right + "\n");
                unordered_set<string> resultsFromRight = getRHS(right);
                results.insert(resultsFromRight.begin(), resultsFromRight.end());
            }
        }
    }
    return results;
}

unordered_set<string> CachedNextTRelationship::getLHS(string rhs) {
    unordered_set<string> results;
    if(getLhsHistory.isInHistory(rhs)) {
        printStmt("retrieving NextT getLHS"  + rhs + " from storage\n");
        results = CachedManyToManyRelationship::getLHS(rhs);
    } else {
        printStmt("computing NextT LHS " + rhs + "\n");
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
