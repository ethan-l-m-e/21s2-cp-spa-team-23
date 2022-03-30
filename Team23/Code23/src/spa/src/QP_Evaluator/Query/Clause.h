//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <utility>
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
    explicit Clause(vector<Argument> argList): argList{std::move(argList)} {};
    virtual ~Clause()= default;
} Clause;

typedef struct SuchThatClause : Clause {
    RelRef relRef;
    explicit SuchThatClause(vector<Argument> argList, RelRef relRef): Clause(std::move(argList)), relRef{relRef} {};
} SuchThatClause;

typedef struct PatternClause : Clause {
    SynonymType synonymType;
    explicit PatternClause(vector<Argument> argList, SynonymType synonymType): Clause(std::move(argList)), synonymType{synonymType} {};
} PatternClause;

typedef struct WithClause : Clause {
    explicit WithClause(vector<Argument> argList): Clause(std::move(argList)) {};
} WithClause;

typedef struct ResultClause : Clause {
    explicit ResultClause(vector<Argument> argList): Clause(std::move(argList)) {};
} ResultClause;

#endif //SPA_CLAUSE_H
