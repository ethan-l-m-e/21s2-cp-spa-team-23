//
// Created by Karan Dev Sapra on 22/3/22.
//

#ifndef SPA_CACHE_H
#define SPA_CACHE_H

#include "Cache/CachedRelationships/CachedRelationships.h"

class Cache {

private:
    Cache();

    static Cache *singleton;

public:

    static Cache *getInstance();

    void clearCache();

    struct Relationship {
        CachedNextTRelationship* nextT = CachedNextTRelationship::getInstance();
        CachedAffectsRelationship* affects = CachedAffectsRelationship::getInstance();
        CachedAffectsTRelationship affectsT;
    };

    Relationship relationship;
};


#endif //SPA_CACHE_H
