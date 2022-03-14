#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

using namespace std;

template<class LHS, class RHS>
class GenericTransitiveRelationship {

    unordered_map<LHS, unordered_set<RHS>> lhsToSetRhsMap;

    unordered_map<RHS, unordered_set<LHS>> rhsToSetLhsMap;

    bool isRelationshipNormal(LHS lhs, RHS rhs) {
        if (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) {
            return lhsToSetRhsMap[lhs].find(rhs) != lhsToSetRhsMap[lhs].end();
        } else {
            return false;
        }
    }

    unordered_set<RHS> getSetRhsNormal(LHS lhs) {

        unordered_set<RHS> emptySet;

        return (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) ? lhsToSetRhsMap[lhs] : emptySet;
    }

    unordered_set<LHS> getSetLhsNormal(RHS rhs) {

        unordered_set<LHS> emptySet;

        return (rhsToSetLhsMap.find(rhs) != rhsToSetLhsMap.end()) ? rhsToSetLhsMap[rhs] : emptySet;
    }


public:
    void setRelationship(LHS lhs, RHS rhs) {
        if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
            lhsToSetRhsMap.emplace(lhs, unordered_set<RHS>{rhs});
        } else {
            lhsToSetRhsMap[lhs].insert(rhs);
        }

        if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
            rhsToSetLhsMap.emplace(rhs, unordered_set<LHS>{lhs});
        } else {
            rhsToSetLhsMap[rhs].insert(lhs);
        }
    }

    bool isRelationship(string lhs, string rhs) {
        return isRelationshipNormal(std::stoi(lhs), std::stoi(rhs));
    }

    unordered_set<string> getSetRHS(string lhs) {
        return convertSetGenericsToSetStrings(getSetRhsNormal(std::stoi(lhs)));
    }

    unordered_set<string> getSetLHS(string rhs) {
        return convertSetGenericsToSetStrings(getSetLhsNormal(std::stoi(rhs)));
    }


    void clear() {
        lhsToSetRhsMap.clear();
        rhsToSetLhsMap.clear();
    }





};

