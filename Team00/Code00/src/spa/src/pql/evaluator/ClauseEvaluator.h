//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H


#include <utility>
#include <vector>
#include "Result.h"
#include "pql/query_obj/Argument.h"
#include "PKB.h"
#include "pql/query_obj/Query.h"


class ClauseEvaluator {
protected:
    std::vector<Argument> argList;
    PKB* pkb;
    Query* query;
public:
    ClauseEvaluator(std::vector<Argument> args, PKB* pkb,  Query* query) : argList(std::move(args)),  pkb(pkb), query(query){}
    virtual Result evaluateClause();
    bool hasTwoSynonyms();
    bool hasNoSynonyms();
    bool leftIsSynonym();
    bool rightIsSynonym();
    Result buildResult(ResultType type, ResultHeader header, vector<ResultItem> items);
};


#endif //SPA_CLAUSEEVALUATOR_H