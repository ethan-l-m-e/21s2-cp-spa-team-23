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
    virtual ~Clause()= default;
} Clause;

typedef struct SuchThatClause : Clause {
    RelRef relRef;
    string getName()
    {
        return "such that clause: " + std::get<string>(argList[0].argumentValue) + " " + std::get<string>(argList[1].argumentValue);
    }
} SuchThatClause;

typedef struct PatternClause : Clause {
    SynonymType synonymType;
    string getName()
    {
        return "pattern clause: " + std::get<string>(argList[0].argumentValue) + " " + std::get<string>(argList[1].argumentValue);
    }
} PatternClause;

typedef struct WithClause : Clause {
    string getName()
    {
        return "with clause: " + (argList[0].argumentType == ArgumentType::ATTR_REF ?
                                     std::get<pair<string, AttrName>>(argList[0].argumentValue).first :
                                     std::get<string>(argList[0].argumentValue)) + " " +
                (argList[1].argumentType == ArgumentType::ATTR_REF ?
                 std::get<pair<string, AttrName>>(argList[1].argumentValue).first :
                 std::get<string>(argList[1].argumentValue));
    }
} WithClause;

typedef struct ResultClause : Clause {
} ResultClause;

#endif //SPA_CLAUSE_H
