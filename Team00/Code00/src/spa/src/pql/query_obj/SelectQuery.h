//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SELECTQUERY_H
#define SPA_SELECTQUERY_H


#include "Query.h"

class SelectQuery : public Query {
public:
    std::string generateResult(PKB* pkb) override {
        // find variable/statements

        // find relationships if any

        // find pattern-cl if any
        std::string patternResults = patternClause.query(pkb);

        return {
                // intersected results
        };
    }
};


#endif //SPA_SELECTQUERY_H
