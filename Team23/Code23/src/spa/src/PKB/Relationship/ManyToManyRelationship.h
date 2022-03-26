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
class ManyToManyRelationship : public AbstractManyToManyRelationship<LHS, RHS> {

    unordered_map<LHS, unordered_set<RHS>> lhsToSetRhsMap;

    unordered_map<RHS, unordered_set<LHS>> rhsToSetLhsMap;

    bool isRelationshipNormal(LHS lhs, RHS rhs) {
        if (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) {
            return lhsToSetRhsMap[lhs].find(rhs) != lhsToSetRhsMap[lhs].end();
        } else {
            return false;
        }
    }

    unordered_set<RHS> getRHSNormal(LHS lhs) {

        unordered_set<RHS> emptySet;

        return (lhsToSetRhsMap.find(lhs) != lhsToSetRhsMap.end()) ? lhsToSetRhsMap[lhs] : emptySet;
    }

    unordered_set<LHS> getLHSNormal(RHS rhs) {

        unordered_set<LHS> emptySet;

        return (rhsToSetLhsMap.find(rhs) != rhsToSetLhsMap.end()) ? rhsToSetLhsMap[rhs] : emptySet;
    }


    LHS convertToLHS(string s, LHS&);
    RHS convertToRHS(string s, RHS&);

public:
    void setRelationship(LHS lhs, RHS rhs) override {
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

    void setRelationship(LHS lhs, unordered_set<RHS> setRhs) override {
        lhsToSetRhsMap[lhs] = setRhs;

        for (RHS rhs : setRhs) {
            if (rhsToSetLhsMap.find(rhs) == rhsToSetLhsMap.end()) {
                rhsToSetLhsMap.emplace(rhs, unordered_set<LHS>{lhs});
            } else {
                rhsToSetLhsMap[rhs].insert(lhs);
            }
        }
    }

    void setRelationship(unordered_set<LHS> setLhs, RHS rhs) override {
        rhsToSetLhsMap[rhs] = setLhs;

        for (LHS lhs : setLhs) {
            if (lhsToSetRhsMap.find(lhs) == lhsToSetRhsMap.end()) {
                lhsToSetRhsMap.emplace(lhs, unordered_set<RHS>{rhs});
            } else {
                lhsToSetRhsMap[lhs].insert(rhs);
            }
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
        lhsToSetRhsMap.clear();
        rhsToSetLhsMap.clear();
    }





};





template<> inline string ManyToManyRelationship<string, string>::convertToLHS(string s, string&) {
    return s;
}
template<> inline string ManyToManyRelationship<string, int>::convertToLHS(string s, string&) {
    return s;
}
template<> inline int ManyToManyRelationship<int, string>::convertToLHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int ManyToManyRelationship<int, int>::convertToLHS(string s, int&) {
    return std::stoi(s);
}


template<> inline string ManyToManyRelationship<string, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline string ManyToManyRelationship<int, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline int ManyToManyRelationship<string , int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int ManyToManyRelationship<int, int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}