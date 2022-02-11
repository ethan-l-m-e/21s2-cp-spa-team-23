//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_SELECTCLAUSEEVALUATOR_H
#define SPA_SELECTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SelectClauseEvaluator : public ClauseEvaluator {
public:
    SelectClauseEvaluator (SynonymRelations* nTuple, PKB* pkb, Query* query) : synonymRelations(nTuple), ClauseEvaluator(pkb, query) {};
    Result evaluateClause() override;
private:
    SynonymRelations* synonymRelations;
};


#endif //SPA_SELECTCLAUSEEVALUATOR_H
