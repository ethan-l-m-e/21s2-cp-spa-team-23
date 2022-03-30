//
// Created by Karan Dev Sapra on 22/3/22.
//

#ifndef SPA_CACHEDNEXTTRELATIONSHIP_H
#define SPA_CACHEDNEXTTRELATIONSHIP_H

#include "CachedManyToManyRelationship.h"

class CachedNextTRelationship : public CachedManyToManyRelationship {

public:

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;
};


#endif //SPA_CACHEDNEXTTRELATIONSHIP_H
