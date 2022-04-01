//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsRelationship.h"

bool CachedAffectsRelationship::isRelationship(string lhs, string rhs) {
    bool boolResults;
    //checks if result (returning true) exist or if query is inside history
    if(pairHistory.isInHistory(lhs, rhs) || CachedManyToManyRelationship::isRelationship(lhs, rhs)) {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = CachedManyToManyRelationship::isRelationship(lhs, rhs);
    } else {
        pairHistory.addToHistory(lhs, rhs);
        boolResults = affectsOp->computeRelation(lhs, rhs);
        if (boolResults) CachedManyToManyRelationship::setRelationship(lhs, rhs);
    }
    return boolResults;
}

unordered_set<string> CachedAffectsRelationship::getRHS(string lhs) {
    unordered_set<string> results;
    if(getRhsHistory.isInHistory(lhs) || CachedManyToManyRelationship::getRHS(lhs).size() > 0) {
        getRhsHistory.addToHistory(lhs);
        results = CachedManyToManyRelationship::getRHS(lhs);
    } else {
        getRhsHistory.addToHistory(lhs);
        unordered_set<string> allStmtNo = nextT->getRHS(lhs);//getAllStmtInSameProcedureAs(lhs);

        for(string right: allStmtNo) {
            if(isRelationship(lhs, right)) results.insert(right);
        }
    }
    return results;
}

unordered_set<string> CachedAffectsRelationship::getLHS(string rhs) {
    unordered_set<string> results;
    if(getLhsHistory.isInHistory(rhs) || CachedManyToManyRelationship::getLHS(rhs).size() > 0) {
        getLhsHistory.addToHistory(rhs);
        results = CachedManyToManyRelationship::getLHS(rhs);
    } else {
        getLhsHistory.addToHistory(rhs);
        unordered_set<string> allStmtNo = nextT->getLHS(rhs);//getAllStmtInSameProcedureAs(rhs);
        for(string left: allStmtNo) {
            if(isRelationship(left, rhs)) results.insert(left);
        }
    }
    return results;
}

CachedAffectsRelationship *CachedAffectsRelationship::singleton = nullptr;
CachedAffectsRelationship *CachedAffectsRelationship::getInstance() {
    if (CachedAffectsRelationship::singleton == nullptr) {
        CachedAffectsRelationship::singleton = new CachedAffectsRelationship;
    }
    return CachedAffectsRelationship::singleton;
}