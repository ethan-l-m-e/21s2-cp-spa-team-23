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
class OneToOneRelationship {

    unordered_map<LHS, RHS> lhsToRhsMap;

    unordered_map<RHS, LHS> rhsToLhsMap;


    bool isRelationshipNormal(LHS lhs, RHS rhs) {
        if (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) {
            return lhsToRhsMap[lhs] == rhs;
        } else {
            return false;
        }
    }



    LHS convertToLHS(string s, LHS&);
    RHS convertToRHS(string s, RHS&);

public:
    void setRelationship(LHS lhs, RHS rhs) {
        lhsToRhsMap.emplace(lhs, rhs);
        rhsToLhsMap.emplace(rhs, lhs);
    }


    bool isRelationship(string lhs, string rhs) {
        LHS l;
        RHS r;
        return isRelationshipNormal(convertToLHS(lhs, l), convertToRHS(rhs, r));
    }

    unordered_set<RHS> getRHSNormal(LHS lhs) {
        unordered_set<RHS> emptySet;

        return (lhsToRhsMap.find(lhs) != lhsToRhsMap.end()) ? unordered_set<RHS>{lhsToRhsMap[lhs]} : emptySet;
    }

    unordered_set<LHS> getLHSNormal(RHS rhs) {
        unordered_set<LHS> emptySet;

        return (rhsToLhsMap.find(rhs) != rhsToLhsMap.end()) ? unordered_set<LHS>{rhsToLhsMap[rhs]} : emptySet;
    }


    unordered_set<string> getRHS(string lhs) {
        LHS l;
        return convertSetGenericsToSetStrings(getRHSNormal(convertToLHS(lhs, l)));
    }

    unordered_set<string> getLHS(string rhs) {
        RHS r;
        return convertSetGenericsToSetStrings(getLHSNormal(convertToRHS(rhs, r)));
    }




    void clear() {
        lhsToRhsMap.clear();
        rhsToLhsMap.clear();
    }



};


template<> inline string OneToOneRelationship<string, string>::convertToLHS(string s, string&) {
    return s;
}
template<> inline string OneToOneRelationship<string, int>::convertToLHS(string s, string&) {
    return s;
}
template<> inline int OneToOneRelationship<int, string>::convertToLHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int OneToOneRelationship<int, int>::convertToLHS(string s, int&) {
    return std::stoi(s);
}


template<> inline string OneToOneRelationship<string, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline string OneToOneRelationship<int, string>::convertToRHS(string s, string&) {
    return s;
}
template<> inline int OneToOneRelationship<string , int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}
template<> inline int OneToOneRelationship<int, int>::convertToRHS(string s, int&) {
    return std::stoi(s);
}
