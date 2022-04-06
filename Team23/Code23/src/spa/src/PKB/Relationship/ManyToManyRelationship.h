#ifndef SPA_MANYTOMANYRELATIONSHIP_H
#define SPA_MANYTOMANYRELATIONSHIP_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

#include <unordered_set>
#include <unordered_map>

#include "AbstractManyToManyRelationship.h"

using namespace std;

class ManyToManyRelationship : public AbstractManyToManyRelationship {

    unordered_map<string, unordered_set<string>> lhsToSetRhsMap;
    unordered_map<string, unordered_set<string>> rhsToSetLhsMap;

public:
    void setRelationship(string lhs, string rhs) override;
    void setRelationship(string lhs, unordered_set<string> setRhs) override;
    void setRelationship(unordered_set<string> setLhs, string rhs) override;
    bool isRelationship(string lhs, string rhs) override;
    unordered_set<string> getRHS(string lhs) override;
    unordered_set<string> getLHS(string rhs) override;
    void clear() override;

};


#endif //SPA_MANYTOMANYRELATIONSHIP_H