//
// Created by Karan Dev Sapra on 22/3/22.
//

#include "CachedAffectsRelationship.h"

void CachedAffectsRelationship::setRelationship(int lhs, int rhs) {

}

bool CachedAffectsRelationship::isRelationship(string lhs, string rhs) {
    return false;
}

unordered_set<string> CachedAffectsRelationship::getRHS(string lhs) {
    return unordered_set<string>();
}

unordered_set<string> CachedAffectsRelationship::getLHS(string rhs) {
    return unordered_set<string>();
}

void CachedAffectsRelationship::clear() {

}
