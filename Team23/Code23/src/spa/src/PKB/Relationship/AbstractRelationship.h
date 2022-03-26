//
// Created by Karan Dev Sapra on 22/3/22.
//

#pragma once

#ifndef SPA_ABSTRACTRELATIONSHIP_H
#define SPA_ABSTRACTRELATIONSHIP_H


#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;

template<class LHS, class RHS>
class AbstractRelationship {

    virtual void setRelationship(LHS lhs, RHS rhs) = 0;

    virtual bool isRelationship(string lhs, string rhs) = 0;

    virtual unordered_set<string> getRHS(string lhs) = 0;

    virtual unordered_set<string> getLHS(string rhs) = 0;

    virtual void clear() = 0;

};


#endif //SPA_ABSTRACTRELATIONSHIP_H
