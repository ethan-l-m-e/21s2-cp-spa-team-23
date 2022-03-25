//
// Created by Tianyi Wang on 26/3/22.
//

#ifndef SPA_WITHCLAUSEEVALUATOR_H
#define SPA_WITHCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"

class WithClauseEvaluator : public ClauseEvaluator {
public:
    WithClauseEvaluator(unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): ClauseEvaluator(declarations, clause, pkb) {};
    bool evaluateClause(ResultTable* resultTable) override;
protected:

    Argument argLeft = clause->argList[0];
    Argument argRight = clause->argList[1];

};


#endif //SPA_WITHCLAUSEEVALUATOR_H
