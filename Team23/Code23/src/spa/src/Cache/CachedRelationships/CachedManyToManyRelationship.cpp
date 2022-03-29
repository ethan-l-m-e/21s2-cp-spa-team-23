//
// Created by Karan Dev Sapra on 29/3/22.
//

#include "CachedManyToManyRelationship.h"


bool CachedManyToManyRelationship::isInHistory(string lhs, string rhs) {
    tuple<string, string> tup = make_tuple(lhs, rhs);

    return history.find(tup) != history.end();
}

void CachedManyToManyRelationship::addToHistory(string lhs, string rhs) {
    tuple<string, string> tup = make_tuple(lhs, rhs);

    history.insert(tup);
}
