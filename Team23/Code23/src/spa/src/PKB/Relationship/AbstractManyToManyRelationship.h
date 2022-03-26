//
// Created by Karan Dev Sapra on 22/3/22.
//

#pragma once

#include "AbstractRelationship.h"

#ifndef SPA_ABSTRACTMANYTOMANYRELATIONSHIP_H
#define SPA_ABSTRACTMANYTOMANYRELATIONSHIP_H


#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;

template<class LHS, class RHS>
class AbstractManyToManyRelationship : public AbstractRelationship<LHS, RHS> {

    virtual void setRelationship(LHS lhs, unordered_set<RHS> setRhs) = 0;

    virtual void setRelationship(unordered_set<LHS> setLhs, RHS rhs) = 0;


};


#endif //SPA_ABSTRACTMANYTOMANYRELATIONSHIP_H
