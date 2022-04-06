#include "ManyToManyRelationship.h"

void ManyToManyRelationship::setRelationship(string lhs, string rhs) {
    if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
        lhsToSetRhsMap.emplace(lhs, unordered_set<string>{rhs});
    } else {
        lhsToSetRhsMap[lhs].insert(rhs);
    }

    if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
        rhsToSetLhsMap.emplace(rhs, unordered_set<string>{lhs});
    } else {
        rhsToSetLhsMap[rhs].insert(lhs);
    }
}

void ManyToManyRelationship::setRelationship(string lhs, unordered_set<string> setRhs) {
    lhsToSetRhsMap[lhs] = setRhs;

    for (string rhs : setRhs) {
        if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
            rhsToSetLhsMap.emplace(rhs, unordered_set<string>{lhs});
        } else {
            rhsToSetLhsMap[rhs].insert(lhs);
        }
    }
}

void ManyToManyRelationship::setRelationship(unordered_set<string> setLhs, string rhs) {
    rhsToSetLhsMap[rhs] = setLhs;

    for (string lhs : setLhs) {
        if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
            lhsToSetRhsMap.emplace(lhs, unordered_set<string>{rhs});
        } else {
            lhsToSetRhsMap[lhs].insert(rhs);
        }
    }
}

bool ManyToManyRelationship::isRelationship(string lhs, string rhs) {
    if (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) {
        return lhsToSetRhsMap[lhs].find(rhs) != lhsToSetRhsMap[lhs].end();
    } else {
        return false;
    }
}

unordered_set<string> ManyToManyRelationship::getRHS(string lhs) {

    unordered_set<string> emptySet;

    return (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) ? lhsToSetRhsMap[lhs] : emptySet;
}

unordered_set<string> ManyToManyRelationship::getLHS(string rhs) {

    unordered_set<string> emptySet;

    return (rhsToSetLhsMap.find(rhs) != rhsToSetLhsMap.end()) ? rhsToSetLhsMap[rhs] : emptySet;
}


void ManyToManyRelationship::clear() {
    lhsToSetRhsMap.clear();
    rhsToSetLhsMap.clear();
}