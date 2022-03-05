//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_SELECTCLAUSEEVALUATOR_H
#define SPA_SELECTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SelectClauseEvaluator : public ClauseEvaluator {
public:
    SelectClauseEvaluator (PKB* pkb, Query* query) : ClauseEvaluator(pkb, query) {};
    bool evaluateClause(ResultTable* resultTable) override;
};


#endif //SPA_SELECTCLAUSEEVALUATOR_H
