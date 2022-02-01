//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H


#include <vector>
#include "Result.h"
#include "Argument.h"

enum class RelRef{
    FOLLOWS,
    FOLLOWS_T,
    PARENT,
    PARENT_T,
    USES_S,
    USES_P,
    MODIFIES_S,
    MODIFIES_P
};

class Clause {
private:
    std::vector<Argument> argList;
public:
    Clause(std::vector<Argument> args) : argList(args) {}
    virtual Result evaluateClause();
};


#endif //SPA_CLAUSE_H
