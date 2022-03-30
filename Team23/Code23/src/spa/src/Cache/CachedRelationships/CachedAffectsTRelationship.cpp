//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsTRelationship.h"


bool CachedAffectsTRelationship::isRelationship(string lhs, string rhs) {
    bool defaultReturn = CachedManyToManyRelationship::isRelationship(lhs, lhs);

    return defaultReturn;
}

unordered_set<string> CachedAffectsTRelationship::getRHS(string lhs) {
    unordered_set<string> defaultReturn = CachedManyToManyRelationship::getRHS(lhs);

    return defaultReturn;
}

unordered_set<string> CachedAffectsTRelationship::getLHS(string rhs) {
    unordered_set<string> defaultReturn = CachedManyToManyRelationship::getLHS(rhs);

    return defaultReturn;
}
