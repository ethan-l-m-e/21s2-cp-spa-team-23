//
// Created by Karan Dev Sapra on 22/3/22.
//

#ifndef SPA_CACHEDNEXTTRELATIONSHIP_H
#define SPA_CACHEDNEXTTRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

class CachedNextTRelationship : public AbstractManyToManyRelationship<int, int> {

public:
    void setRelationship(int lhs, int rhs) override;

    virtual void setRelationship(int lhs, unordered_set<int> setRhs) override;

    virtual void setRelationship(unordered_set<int> setLhs, int rhs) override;

    bool isRelationship(string lhs, string rhs) override;

    unordered_set<string> getRHS(string lhs) override;

    unordered_set<string> getLHS(string rhs) override;

    void clear() override;
};


#endif //SPA_CACHEDNEXTTRELATIONSHIP_H
