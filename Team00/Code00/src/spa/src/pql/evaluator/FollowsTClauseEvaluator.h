//
// Created by Tianyi Wang on 10/2/22.
//

#ifndef SPA_FOLLOWSTCLAUSEEVALUATOR_H
#define SPA_FOLLOWSTCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class FollowsTClauseEvaluator : public SuchThatClauseEvaluator {
    public:
        FollowsTClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
        Result evaluateClause() override;
        RelRef getRelRef() override {return RelRef::FOLLOWS_T;};
        vector<ResultItem> generateTuples (unordered_set<std::string> &leftSet, unordered_set<std::string> &rightSet) override;
};


#endif //SPA_FOLLOWSTCLAUSEEVALUATOR_H
