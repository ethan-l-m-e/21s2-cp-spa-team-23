//
// Created by Tianyi Wang on 5/2/22.
//

#ifndef SPA_FOLLOWSCLAUSEEVALUATOR_H
#define SPA_FOLLOWSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class FollowsClauseEvaluator : public SuchThatClauseEvaluator {
    public:
        FollowsClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
        Result evaluateClause() override;
        RelRef getRelRef() override {return RelRef::FOLLOWS;};
        vector<ResultItem> generateTuples (unordered_set<std::string> &leftSet, unordered_set<std::string> &rightSet) override;
};


#endif //SPA_FOLLOWSCLAUSEEVALUATOR_H
