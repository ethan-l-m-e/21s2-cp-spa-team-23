//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SUCHTHATCLAUSE_H
#define SPA_SUCHTHATCLAUSE_H


#include "Clause.h"

class SuchThatClause : public Clause {
public:
    Result evaluateClause() override {
        return {};
    }
};


#endif //SPA_SUCHTHATCLAUSE_H
