//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsRelationship.h"

bool CachedAffectsRelationship::isRelationship(string lhs, string rhs) {
    bool defaultReturn = CachedManyToManyRelationship::isRelationship(lhs, lhs);

    return defaultReturn;
}

unordered_set<string> CachedAffectsRelationship::getRHS(string lhs) {
    unordered_set<string> defaultReturn = CachedManyToManyRelationship::getRHS(lhs);

    return defaultReturn;
}

unordered_set<string> CachedAffectsRelationship::getLHS(string rhs) {
    unordered_set<string> defaultReturn = CachedManyToManyRelationship::getLHS(rhs);

    return defaultReturn;
}
