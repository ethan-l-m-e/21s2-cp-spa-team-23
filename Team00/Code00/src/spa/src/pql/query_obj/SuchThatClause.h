//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SUCHTHATCLAUSE_H
#define SPA_SUCHTHATCLAUSE_H


#include <vector>
#include "Clause.h"

class SuchThatClause : public Clause {
private:
    RelRef relRef;
public:
    SuchThatClause(RelRef relRef, std::vector<Argument> args) : relRef{relRef}, Clause(args) {}
    Result evaluateClause() override {
        return {};
    }
};


#endif //SPA_SUCHTHATCLAUSE_H
