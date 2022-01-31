//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "PKB.h"
#include "PatternClause.h"

class Query {
protected:
//declarations
//...
//clauses: such-that-cl, pattern-cl
//...
PatternClause patternClause;
public:
    virtual std::string generateResult(PKB* pkb);
};


#endif //SPA_QUERY_H
