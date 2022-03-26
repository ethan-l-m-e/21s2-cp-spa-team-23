//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <vector>
#include "Argument.h"

using std::vector;

enum class RelRef{
    FOLLOWS,
    FOLLOWS_T,
    PARENT,
    PARENT_T,
    USES_S,
    USES_P,
    MODIFIES_S,
    MODIFIES_P,
    CALLS,
    CALLS_T,
    NEXT,
    NEXT_T,
    AFFECTS,
    AFFECTS_T
};

enum class SynonymType {
    ASSIGN,
    WHILE,
    IF
};

typedef struct Clause {
    vector<Argument> argList;
} Clause;

typedef struct SuchThatClause : Clause {
    RelRef relRef;
} SuchThatClause;

typedef struct PatternClause : Clause {
    SynonymType synonymType;
} PatternClause;

typedef struct WithClause : Clause {
} WithClause;

typedef struct ResultClause : Clause {
} ResultClause;



#endif //SPA_CLAUSE_H
