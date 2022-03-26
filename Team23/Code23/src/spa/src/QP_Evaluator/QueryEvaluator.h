//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include "PKB/PKB.h"
#include "QP_Evaluator/Query/Query.h"
#include "QP_Evaluator/ClauseEvaluators/Result.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluator.h"

#include <list>

using std::string;
using std::list;

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    list<string> evaluate(Query*);

    ClauseEvaluator* generateEvaluator(SuchThatClause&, Query&);

    static list<string> generateResultString(ResultTable*);
};


#endif //SPA_QUERYEVALUATOR_H
