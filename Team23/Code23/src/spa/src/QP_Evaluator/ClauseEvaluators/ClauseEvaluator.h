//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H

#include "QP_Evaluator/Query/Query.h"
#include "PKB/PKB.h"
#include "Result.h"
#include "ResultTable.h"

class ClauseEvaluator {
protected:
    vector<Argument> argList;
    PKB* pkb;
    Query* query;
    Result result;
    void mergeResult(ResultTable* resultTable);

public:
    ClauseEvaluator(vector<Argument> args, PKB* pkb,  Query* query) : argList(std::move(args)),  pkb(pkb), query(query){}
    ClauseEvaluator(PKB* pkb,  Query* query) : pkb(pkb), query(query){}
    virtual ~ClauseEvaluator() = default;
    virtual bool evaluateClause(ResultTable* resultTable) = 0;
    unordered_set<string> getAllType(DesignEntity designEntity);

};


#endif //SPA_CLAUSEEVALUATOR_H
