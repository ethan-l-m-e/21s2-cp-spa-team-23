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
    Clause* clause;
    unordered_map<string, DesignEntity>* declarations;
    PKB* pkb;
    Result result;
    bool processResult(ResultTable* resultTable);

public:
    ClauseEvaluator(unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb) : declarations(declarations), clause(clause),  pkb(pkb){}
    ClauseEvaluator(unordered_map<string, DesignEntity>* declarations, PKB* pkb) : declarations(declarations),  pkb(pkb){}

    virtual ~ClauseEvaluator() = default;
    virtual bool evaluateClause(ResultTable* resultTable) = 0;
    unordered_set<string> getAllType(DesignEntity designEntity);

};


#endif //SPA_CLAUSEEVALUATOR_H
