//
// Created by リム・イーサン on 31/1/22.
//
// Created by Tianyi Wang on 5/2/22.
//

#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <string>
#include <variant>
#include <vector>
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

enum class SynonymType { ASSIGN };

typedef struct Clause {
    std::vector<Argument> argList;
} Clause;

typedef struct SuchThatClause : Clause {
    RelRef relRef;
} SuchThatClause;

typedef struct PatternClause : Clause {
    SynonymType synonymType;
} PatternClause;



#endif //SPA_CLAUSE_H
