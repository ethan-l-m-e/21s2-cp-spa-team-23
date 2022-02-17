//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H

#include <vector>
#include "ClauseEvaluator.h"
#include "pql/query_obj/Argument.h"

class PatternClauseEvaluator : public ClauseEvaluator {
public:
    PatternClauseEvaluator (SynonymType synonymType, std::vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {}
    Result evaluateClause() override;
protected:

    bool leftIsSynonym();
    bool leftIsFixed();
    bool leftIsWildCard();
    bool rightIsWildCard();
    bool rightIsPartWildCard();

    Argument assignSynonym = argList[0];
    Argument argLeft = argList[1];
    Argument argRight = argList[2];

};


#endif //SPA_PATTERNCLAUSEEVALUATOR_H