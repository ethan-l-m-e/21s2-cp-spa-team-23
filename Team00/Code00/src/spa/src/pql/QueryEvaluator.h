//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "pql/query_obj/Query.h"
#include "pql/ClauseEvaluators/Result.h"
#include "pql/ClauseEvaluators/ClauseEvaluator.h"
#include "pql/ClauseEvaluators/FollowsClauseEvaluator.h"
#include "pql/ClauseEvaluators/PatternClauseEvaluator.h"
#include "pql/ClauseEvaluators/SelectClauseEvaluator.h"
#include <sstream>
#include <iostream>
#include <list>

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    std::list<std::string> evaluate(Query* query);

    ClauseEvaluator* generateEvaluator(SuchThatClause clause, Query* query);

    static void mergeResultToSynonymsRelations(SynonymRelations* sr, Result result);

    static std::list<std::string> generateResultString(SynonymRelations* sr, string selectedSynonym);
};


#endif //SPA_QUERYEVALUATOR_H
