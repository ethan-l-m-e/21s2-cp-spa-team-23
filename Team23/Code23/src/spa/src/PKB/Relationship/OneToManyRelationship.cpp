#include "OneToManyRelationship.h"

void OneToManyRelationship::setRelationship(string lhs, string rhs) {

    rhsToLhs.emplace(rhs, lhs);

    if (lhsToRhsMap.find(lhs) == lhsToRhsMap.end()) {
        lhsToRhsMap.emplace(lhs, unordered_set<string>{rhs});
    } else {
        lhsToRhsMap[lhs].insert(rhs);
    }

}

bool OneToManyRelationship::isRelationship(string lhs, string rhs) {
    if (rhsToLhs.find(rhs) != rhsToLhs.end()) {
        return rhsToLhs[rhs] == lhs;
    } else {
        return false;
    }
}


unordered_set<string> OneToManyRelationship::getRHS(string lhs) {

    unordered_set<string> emptySet;

    return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? lhsToRhsMap[lhs] : emptySet;
}

unordered_set<string> OneToManyRelationship::getLHS(string rhs) {

    unordered_set<string> emptySet;

    return (rhsToLhs.find(rhs) != rhsToLhs.end()) ? unordered_set<string>{rhsToLhs[rhs]} : emptySet;
}



void OneToManyRelationship::clear() {
    lhsToRhsMap.clear();
    rhsToLhs.clear();
}
