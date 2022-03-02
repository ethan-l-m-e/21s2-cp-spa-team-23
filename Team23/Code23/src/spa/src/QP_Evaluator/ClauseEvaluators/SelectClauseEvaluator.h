//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_SELECTCLAUSEEVALUATOR_H
#define SPA_SELECTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SelectClauseEvaluator : public ClauseEvaluator {
public:
    SelectClauseEvaluator (ResultTable* nTuple, PKB* pkb, Query* query) : resultTable(nTuple), ClauseEvaluator(pkb, query) {};
    Result evaluateClause() override;
private:
    ResultTable* resultTable;
};


#endif //SPA_SELECTCLAUSEEVALUATOR_H
