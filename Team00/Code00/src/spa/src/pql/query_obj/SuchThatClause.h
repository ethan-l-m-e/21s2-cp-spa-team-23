//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SUCHTHATCLAUSE_H
#define SPA_SUCHTHATCLAUSE_H


#include <vector>
#include "Clause.h"

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

class SuchThatClause : public Clause {
private:
    RelRef relRef;
public:
    SuchThatClause(RelRef relRef, std::vector<Argument> args) : relRef{relRef}, Clause(args) {}
    Result evaluateClause(
            PKB* pkb,
            unordered_map<string, DesignEntity> declarations) override {
        return {};
    }
};


#endif //SPA_SUCHTHATCLAUSE_H
