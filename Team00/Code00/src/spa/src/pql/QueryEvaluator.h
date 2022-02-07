//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "pql/query_obj/Query.h"
#include "pql/evaluator/Result.h"
#include "pql/evaluator/ClauseEvaluator.h"
#include "pql/evaluator/FollowsClauseEvaluator.h"
#include "pql/evaluator/PatternClauseEvaluator.h"
#include "pql/evaluator/SelectClauseEvaluator.h"
#include <sstream>
#include <iostream>

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    std::string evaluate(Query* query);

    ClauseEvaluator* generateEvaluator(SuchThatClause clause, Query* query);

    static Result mergeResults(Result r1, Result r2);

    static string convertResultToString(Result result, string selectedSynonym);
};


#endif //SPA_QUERYEVALUATOR_H
