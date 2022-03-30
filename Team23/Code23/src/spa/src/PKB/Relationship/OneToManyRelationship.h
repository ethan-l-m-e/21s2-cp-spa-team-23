#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

#include "AbstractRelationship.h"

using namespace std;


class OneToManyRelationship : public AbstractRelationship {

    unordered_map<string, unordered_set<string>> lhsToRhsMap;

    unordered_map<string, string> rhsToLhs;



public:
    void setRelationship(string lhs, string rhs) override {

        rhsToLhs.emplace(rhs, lhs);

        if (lhsToRhsMap.find(lhs) == lhsToRhsMap.end()) {
            lhsToRhsMap.emplace(lhs, unordered_set<string>{rhs});
        } else {
            lhsToRhsMap[lhs].insert(rhs);
        }

    }

    bool isRelationship(string lhs, string rhs) override {
        if (rhsToLhs.find(rhs) != rhsToLhs.end()) {
            return rhsToLhs[rhs] == lhs;
        } else {
            return false;
        }
    }


    unordered_set<string> getRHS(string lhs) override {

        unordered_set<string> emptySet;

        return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? lhsToRhsMap[lhs] : emptySet;
    }

    unordered_set<string> getLHS(string rhs) override {

        unordered_set<string> emptySet;

        return (rhsToLhs.find(rhs) != rhsToLhs.end()) ? unordered_set<string>{rhsToLhs[rhs]} : emptySet;
    }



    void clear() override {
        lhsToRhsMap.clear();
        rhsToLhs.clear();
    }




};





