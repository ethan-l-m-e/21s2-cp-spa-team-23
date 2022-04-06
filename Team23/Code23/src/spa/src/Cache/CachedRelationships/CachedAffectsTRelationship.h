//
// Created by Karan Dev Sapra on 22/3/22.
//


#ifndef SPA_CACHEDAFFECTSTRELATIONSHIP_H
#define SPA_CACHEDAFFECTSTRELATIONSHIP_H

#include "CachedManyToManyRelationship.h"
#include "CachedAffectsRelationship.h"
#include "CachedNextTRelationship.h"
#include "./Cache/Operators/AffectsTOperator.h"

class CachedAffectsTRelationship : public CachedManyToManyRelationship {

public:

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

protected:
    bool computeRelation(string left, string right);
    unordered_set<string> computeResultSetHelper(string stmt, std::function<unordered_set<string>(string)> computeDirection);
    unordered_set<string> resultSetRecursionHelper(string stmt, std::function<unordered_set<string>(string)> computeDirection);

    static unordered_set<string> callAffectsRHS(string stmt);


    AffectsTOperator* affectsTOp = AffectsTOperator::getInstance();
    CachedNextTRelationship* nextT = CachedNextTRelationship::getInstance();
};


#endif //SPA_CACHEDAFFECTSTRELATIONSHIP_H
