#ifndef SPA_ONETOONERELATIONSHIP_H
#define SPA_ONETOONERELATIONSHIP_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

#include "AbstractRelationship.h"

using namespace std;

class OneToOneRelationship : public AbstractRelationship {

    unordered_map<string, string> lhsToRhsMap;
    unordered_map<string, string> rhsToLhsMap;

public:

    void setRelationship(string lhs, string rhs) override;
    bool isRelationship(string lhs, string rhs) override;
    unordered_set<string> getRHS(string lhs) override;
    unordered_set<string> getLHS(string rhs) override;
    void clear() override;

};


#endif //SPA_ONETOONERELATIONSHIP_H