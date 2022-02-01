//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSE_H
#define SPA_PATTERNCLAUSE_H

#include <vector>
#include "Clause.h"
#include "Argument.h"

class PatternClause : public Clause {
private:
    std::string synonym;
public:
    PatternClause (std::string synonym, std::vector<Argument> args) : synonym{synonym}, Clause(args) {}
    Result evaluateClause() override {
        return {};
    }
};


#endif //SPA_PATTERNCLAUSE_H
