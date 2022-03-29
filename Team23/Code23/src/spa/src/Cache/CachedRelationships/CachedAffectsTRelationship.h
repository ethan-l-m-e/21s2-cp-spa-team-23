//
// Created by Karan Dev Sapra on 22/3/22.
//


#ifndef SPA_CACHEDAFFECTSTRELATIONSHIP_H
#define SPA_CACHEDAFFECTSTRELATIONSHIP_H

#include "CachedManyToManyRelationship.h"

class CachedAffectsTRelationship : public CachedManyToManyRelationship {

public:

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

    void clear() override;
};


#endif //SPA_CACHEDAFFECTSTRELATIONSHIP_H
