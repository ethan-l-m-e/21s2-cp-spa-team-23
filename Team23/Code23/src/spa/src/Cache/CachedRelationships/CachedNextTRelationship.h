//
// Created by Karan Dev Sapra on 22/3/22.
//

#ifndef SPA_CACHEDNEXTTRELATIONSHIP_H
#define SPA_CACHEDNEXTTRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

class CachedNextTRelationship : public ManyToManyRelationship<int, int> {

public:

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

    void clear() override;
};


#endif //SPA_CACHEDNEXTTRELATIONSHIP_H
