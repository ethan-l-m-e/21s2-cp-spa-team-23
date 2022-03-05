//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H

#include <vector>
#include "ClauseEvaluator.h"
#include "QP_Evaluator/Query/Argument.h"
#include "TNode/Node.h"

class PatternClauseEvaluator : public ClauseEvaluator {
public:
    PatternClauseEvaluator (SynonymType synonymType, std::vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {}
    bool evaluateClause(ResultTable* resultTable) override;
protected:

    bool leftIsSynonym();
    bool leftIsIdent();
    bool leftIsWildCard();
    bool rightIsWildCard();
    bool rightIsPartWildCard();
    bool rightIsIdent();

    Argument syn = argList[0];
    Argument arg1 = argList[1];
    Argument arg2 = argList[2];
    Argument arg3;
    // get argument 3 if is if-node
};


#endif //SPA_PATTERNCLAUSEEVALUATOR_H