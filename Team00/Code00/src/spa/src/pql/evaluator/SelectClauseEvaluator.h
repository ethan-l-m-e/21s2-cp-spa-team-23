//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_SELECTCLAUSEEVALUATOR_H
#define SPA_SELECTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SelectClauseEvaluator : public ClauseEvaluator {
public:
    SelectClauseEvaluator (Result result, PKB* pkb, Query* query) : resultReference(result), ClauseEvaluator(pkb, query) {}
    Result evaluateClause() override;
private:
    Result resultReference;
};


#endif //SPA_SELECTCLAUSEEVALUATOR_H
