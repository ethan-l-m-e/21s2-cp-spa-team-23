//
// Created by Tianyi Wang on 5/2/22.
//

#ifndef SPA_FOLLOWSCLAUSEEVALUATOR_H
#define SPA_FOLLOWSCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"

#include <utility>

class FollowsClauseEvaluator : public ClauseEvaluator {
    public:
        FollowsClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : ClauseEvaluator(std::move(args), pkb, query) {}
        Result* evaluateClause() override;
};


#endif //SPA_FOLLOWSCLAUSEEVALUATOR_H
