//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H


#include <vector>
#include "Result.h"
#include "Argument.h"
#include "PKB.h"
#include "Query.h"


class Clause {
protected:
    std::vector<Argument> argList;
public:
    Clause(std::vector<Argument> args) : argList(args) {}
    virtual Result evaluateClause(
            PKB* pkb,
            unordered_map<string, DesignEntity> declarations);
};


#endif //SPA_CLAUSE_H
