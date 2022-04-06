#ifndef SPA_ONETOMANYRELATIONSHIP_H
#define SPA_ONETOMANYRELATIONSHIP_H

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "AbstractRelationship.h"

using namespace std;


class OneToManyRelationship : public AbstractRelationship {

    unordered_map<string, unordered_set<string>> lhsToRhsMap;
    unordered_map<string, string> rhsToLhs;

public:
    void setRelationship(string lhs, string rhs) override;
    bool isRelationship(string lhs, string rhs) override;
    unordered_set<string> getRHS(string lhs) override;
    unordered_set<string> getLHS(string rhs) override;
    void clear() override;

};

#endif //SPA_ONETOMANYRELATIONSHIP_H



