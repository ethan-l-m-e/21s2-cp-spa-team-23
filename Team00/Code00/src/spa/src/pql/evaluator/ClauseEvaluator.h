//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H


#include <vector>
#include "Result.h"
#include "pql/query_obj/Argument.h"
#include "PKB.h"
#include "pql/query_obj/Query.h"


class ClauseEvaluator {
protected:
    std::vector<Argument> argList;
public:
    ClauseEvaluator(std::vector<Argument> args) : argList(args) {}
    virtual Result evaluateClause(
            PKB* pkb,
            unordered_map<string, DesignEntity> declarations);
};


#endif //SPA_CLAUSEEVALUATOR_H
