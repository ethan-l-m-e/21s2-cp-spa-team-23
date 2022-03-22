//
// Created by Karan Dev Sapra on 22/3/22.
//

#ifndef SPA_CACHEDAFFECTSRELATIONSHIP_H
#define SPA_CACHEDAFFECTSRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

class CachedAffectsRelationship : public AbstractRelationship<int, int> {


public:
    void setRelationship(int lhs, int rhs) override;

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

    void clear() override;
};


#endif //SPA_CACHEDAFFECTSRELATIONSHIP_H
