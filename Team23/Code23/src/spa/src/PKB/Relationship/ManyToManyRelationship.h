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
class ManyToManyRelationship {

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


    LHS convertToLHS(string s, LHS&);
    RHS convertToRHS(string s, RHS&);

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
        LHS l;
        RHS r;
        return isRelationshipNormal(convertToLHS(lhs, l), convertToRHS(rhs, r));
    }

    unordered_set<string> getSetRHS(string lhs) {
        LHS l;
        return convertSetGenericsToSetStrings(getSetRhsNormal(convertToLHS(lhs, l)));
    }

    unordered_set<string> getSetLHS(string rhs) {
        RHS r;
        return convertSetGenericsToSetStrings(getSetLhsNormal(convertToRHS(rhs, r)));
    }


    void clear() {
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