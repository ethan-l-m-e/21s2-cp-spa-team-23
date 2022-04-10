//
// Created by Karan Dev Sapra on 29/3/22.
//

#ifndef SPA_CACHEDMANYTOMANYRELATIONSHIP_H
#define SPA_CACHEDMANYTOMANYRELATIONSHIP_H

#include "PKB/Relationship/Relationship.h"

#include <set>
#include <vector>
struct History {
    unordered_set<string> historySingle;
    // `unordered_set` cannot have a tuple as a key by default, that's why I am using a `set`
    //set<tuple<string, string>> historyPair;
    set<tuple<string, string>> historyPair;
    bool isInHistory(string key);
    void addToHistory(string key);
    bool isInHistory(string lhs, string rhs);
    void addToHistory(string lhs, string rhs);
    void clear();
};

class CachedManyToManyRelationship : public ManyToManyRelationship {
protected:
    History pairHistory;
    History getLhsHistory;
    History getRhsHistory;

    void printStmt(string input);

public:
    void clear() override;

    unordered_set<string> getAllStmtInSameProcedureAs(string stmt);
};


#endif //SPA_CACHEDMANYTOMANYRELATIONSHIP_H
