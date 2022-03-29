//
// Created by Karan Dev Sapra on 29/3/22.
//

#ifndef SPA_CACHEDMANYTOMANYRELATIONSHIP_H
#define SPA_CACHEDMANYTOMANYRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

#include <set>

class CachedManyToManyRelationship : public ManyToManyRelationship {

    set<tuple<string, string>> history;

protected:
    bool isInHistory(string lhs, string rhs);

    void addToHistory(string lhs, string rhs);

};


#endif //SPA_CACHEDMANYTOMANYRELATIONSHIP_H
