//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSE_H
#define SPA_PATTERNCLAUSE_H


#include "Clause.h"

class PatternClause : public Clause {
public:
    Result evaluateClause() override {
        return {};
    }
};


#endif //SPA_PATTERNCLAUSE_H
