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
class GenericRelationship {

    unordered_map<LHS, RHS> lhsToRhsMap;

    unordered_map<RHS, LHS> rhsToLhsMap;


    bool isRelationshipNormal(LHS lhs, RHS rhs) {
        if (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) {
            return lhsToRhsMap[lhs] == rhs;
        } else {
            return false;
        }
    }

    unordered_set<RHS> getRHSNormal(LHS lhs) {
        unordered_set<RHS> emptySet;

        return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? unordered_set<int>{lhsToRhsMap[lhs]} : emptySet;
    }

    unordered_set<LHS> getLHSNormal(RHS rhs) {
        unordered_set<LHS> emptySet;

        return (rhsToLhsMap.find(rhs) != rhsToLhsMap.end()) ? unordered_set<int>{rhsToLhsMap[rhs]} : emptySet;
    }


public:
    void setRelationship(LHS lhs, RHS rhs) {
        lhsToRhsMap.emplace(lhs, rhs);
        lhsToRhsMap.emplace(rhs, lhs);
    }


    bool isRelationship(string lhs, string rhs) {
        return isRelationshipNormal(std::stoi(lhs), std::stoi(rhs));
    }



    unordered_set<string> getRHS(string lhs) {
        return convertSetGenericsToSetStrings(getRHSNormal(std::stoi(lhs)));
    }

    unordered_set<string> getLHS(string rhs) {
        return convertSetGenericsToSetStrings(getLHSNormal(std::stoi(rhs)));
    }


    void clear() {
        lhsToRhsMap.clear();
        rhsToLhsMap.clear();
    }




};

