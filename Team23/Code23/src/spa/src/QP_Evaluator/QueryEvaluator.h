//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "QP_Evaluator/Query/Query.h"
#include "QP_Evaluator/ClauseEvaluators/Result.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluator.h"

#include <sstream>
#include <iostream>
#include <list>

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    std::list<std::string> evaluate(Query*);

    ClauseEvaluator* generateEvaluator(const SuchThatClause&, Query*);

    static std::list<std::string> generateResultString(ResultTable*);
};


#endif //SPA_QUERYEVALUATOR_H
