//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H


#include <utility>
#include <vector>
#include <cassert>
#include "PKB.h"
#include "Result.h"
#include "ResultTable.h"
#include "QP_Evaluator/Query/Argument.h"
#include "QP_Evaluator/Query/Query.h"


class ClauseEvaluator {
protected:
    std::vector<Argument> argList;
    PKB* pkb;
    Query* query;
    Result result;

public:
    ClauseEvaluator(std::vector<Argument> args, PKB* pkb,  Query* query) : argList(std::move(args)),  pkb(pkb), query(query){}
    ClauseEvaluator(PKB* pkb,  Query* query) : pkb(pkb), query(query){}
    virtual ~ClauseEvaluator() = default;
    virtual Result evaluateClause() = 0;
    unordered_set<std::string> getAllType(DesignEntity designEntity);

};


#endif //SPA_CLAUSEEVALUATOR_H
