//
// Created by Karan Dev Sapra on 6/4/22.
//

#ifndef SPA_MANYTOMANYRELATIONSHIPWITHMINMAX_H
#define SPA_MANYTOMANYRELATIONSHIPWITHMINMAX_H


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

#include <unordered_set>
#include <unordered_map>

#include "ManyToManyRelationship.h"

using namespace std;

class ManyToManyRelationshipWithMinMax : public ManyToManyRelationship {
private:

    unordered_map<string, string> lhsToMinRHSMap;
    unordered_map<string, string> lhsToMaxRHSMap;

public:
    void setRelationship(string lhs, string rhs) override;

    void setRelationship(string lhs, unordered_set<string> setRhs) override;

    void setRelationship(unordered_set<string> setLhs, string rhs) override;

    void clear() override;


    string getRHSMin(string lhs);

    string getRHSMax(string lhs);

};



#endif //SPA_MANYTOMANYRELATIONSHIPWITHMINMAX_H
