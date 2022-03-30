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


class AbstractManyToManyRelationship : public AbstractRelationship {

    virtual void setRelationship(string lhs, unordered_set<string> setRhs) = 0;

    virtual void setRelationship(unordered_set<string> setLhs, string rhs) = 0;


};


#endif //SPA_ABSTRACTMANYTOMANYRELATIONSHIP_H
