//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "PKB.h"
#include "Clause.h"

class Query {
protected:
// MAP<String, string> declarations
    Clause patternClause;
    Clause suchThatClause;
public:
    virtual std::string generateResult(PKB* pkb);
};


#endif //SPA_QUERY_H
