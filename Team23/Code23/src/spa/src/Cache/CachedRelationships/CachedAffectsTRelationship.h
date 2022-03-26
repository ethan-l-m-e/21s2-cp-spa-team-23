//
// Created by Karan Dev Sapra on 22/3/22.
//


#ifndef SPA_CACHEDAFFECTSTRELATIONSHIP_H
#define SPA_CACHEDAFFECTSTRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

class CachedAffectsTRelationship : public ManyToManyRelationship<int, int> {

public:
    void setRelationship(int lhs, int rhs) override;

    void setRelationship(int lhs, unordered_set<int> setRhs) override;

    void setRelationship(unordered_set<int> setLhs, int rhs) override;

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

    void clear() override;
};


#endif //SPA_CACHEDAFFECTSTRELATIONSHIP_H
