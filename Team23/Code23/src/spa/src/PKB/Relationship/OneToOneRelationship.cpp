#include "OneToOneRelationship.h"

void OneToOneRelationship::setRelationship(string lhs, string rhs) {
    lhsToRhsMap.emplace(lhs, rhs);
    rhsToLhsMap.emplace(rhs, lhs);
}


bool OneToOneRelationship::isRelationship(string lhs, string rhs) {
    if (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) {
        return lhsToRhsMap[lhs] == rhs;
    } else {
        return false;
    }
}

unordered_set<string> OneToOneRelationship::getRHS(string lhs) {
    unordered_set<string> emptySet;

    return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? unordered_set<string>{lhsToRhsMap[lhs]} : emptySet;
}

unordered_set<string> OneToOneRelationship::getLHS(string rhs) {
    unordered_set<string> emptySet;

    return (rhsToLhsMap.find(rhs) != rhsToLhsMap.end()) ? unordered_set<string>{rhsToLhsMap[rhs]} : emptySet;
}




void OneToOneRelationship::clear() {
    lhsToRhsMap.clear();
    rhsToLhsMap.clear();
}


