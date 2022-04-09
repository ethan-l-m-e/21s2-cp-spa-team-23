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
public:
    explicit QueryEvaluator(PKB *pkb) : pkb(pkb) {}

    list<string> evaluate(Query *);

    static list<string> generateResultString(ResultTable *);

private:
    PKB *pkb;
    Query *query;

    ClauseEvaluator *generateEvaluator(SuchThatClause &clause, unordered_map<string, DesignEntity> &);

    unordered_set<string> getSelectedSynonyms();

    void mergeToFinalResultTable(ResultTable *finalResultTable, unordered_map<int, ResultTable *> &groupedResultTables,
                                 bool isFalse);
};

#endif //SPA_QUERYEVALUATOR_H
