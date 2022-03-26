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

template<class LHS, class RHS>
class OneToManyRelationship : public AbstractRelationship<LHS, RHS> {

    unordered_map<LHS, unordered_set<RHS>> lhsToRhsMap;

    unordered_map<RHS, LHS> rhsToLhs;


    bool isRelationshipNormal(LHS lhs, RHS rhs) {
        if (rhsToLhs.find(rhs) != rhsToLhs.end()) {
            return rhsToLhs[rhs] == lhs;
        } else {
            return false;
        }
    }

    unordered_set<RHS> getRHSNormal(LHS lhs) {

        unordered_set<RHS> emptySet;

        return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? lhsToRhsMap[lhs] : emptySet;
    }

    unordered_set<LHS> getLHSNormal(RHS rhs) {

        unordered_set<LHS> emptySet;

        return (rhsToLhs.find(rhs) != rhsToLhs.end()) ? unordered_set<LHS>{rhsToLhs[rhs]} : emptySet;
    }


    LHS convertToLHS(string s, LHS&);
    RHS convertToRHS(string s, RHS&);


public:
    void setRelationship(LHS lhs, RHS rhs) override {

        rhsToLhs.emplace(rhs, lhs);

        if (lhsToRhsMap.find(lhs) == lhsToRhsMap.end()) {
            lhsToRhsMap.emplace(lhs, unordered_set<int>{rhs});
        } else {
            lhsToRhsMap[lhs].insert(rhs);
        }

    }

    bool isRelationship(string lhs, string rhs) override {
        LHS l;
        RHS r;
        return isRelationshipNormal(convertToLHS(lhs, l), convertToRHS(rhs, r));
    }



    unordered_set<string> getRHS(string lhs) override {
        LHS l;
        return convertSetGenericsToSetStrings(getRHSNormal(convertToLHS(lhs, l)));
    }


    unordered_set<string> getLHS(string rhs) override {
        RHS r;
        return convertSetGenericsToSetStrings(getLHSNormal(convertToRHS(rhs, r)));
    }




    void clear() override {
        lhsToRhsMap.clear();
        rhsToLhs.clear();
    }




};




template<> inline string OneToManyRelationship<string, string>::convertToLHS(string s, string&) {
    return s;
}
template<> inline string OneToManyRelationship<string, int>::convertToLHS(string s, string&) {
    return s;
}
template<> inline int OneToManyRelationship<int, string>::convertToLHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int OneToManyRelationship<int, int>::convertToLHS(string s, int&) {
    return std::stoi(s);
}


template<> inline string OneToManyRelationship<string, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline string OneToManyRelationship<int, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline int OneToManyRelationship<string , int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int OneToManyRelationship<int, int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}

