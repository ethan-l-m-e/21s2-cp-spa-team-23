#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

#include "AbstractRelationship.h"

using namespace std;

class OneToOneRelationship : public AbstractRelationship {

    unordered_map<string, string> lhsToRhsMap;

    unordered_map<string, string> rhsToLhsMap;



public:

    void setRelationship(string lhs, string rhs) override {
        lhsToRhsMap.emplace(lhs, rhs);
        rhsToLhsMap.emplace(rhs, lhs);
    }


    bool isRelationship(string lhs, string rhs) override {
        if (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) {
            return lhsToRhsMap[lhs] == rhs;
        } else {
            return false;
        }
    }

    unordered_set<string> getRHS(string lhs) override {
        unordered_set<string> emptySet;

        return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? unordered_set<string>{lhsToRhsMap[lhs]} : emptySet;
    }

    unordered_set<string> getLHS(string rhs) override {
        unordered_set<string> emptySet;

        return (rhsToLhsMap.find(rhs) != rhsToLhsMap.end()) ? unordered_set<string>{rhsToLhsMap[rhs]} : emptySet;
    }




    void clear() override {
        lhsToRhsMap.clear();
        rhsToLhsMap.clear();
    }



};


