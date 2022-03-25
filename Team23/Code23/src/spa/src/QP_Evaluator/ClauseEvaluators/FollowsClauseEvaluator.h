//
// Created by Tianyi Wang on 5/2/22.
//

#ifndef SPA_FOLLOWSCLAUSEEVALUATOR_H
#define SPA_FOLLOWSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class FollowsClauseEvaluator : public SuchThatClauseEvaluator {
public:
        FollowsClauseEvaluator (vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
        RelRef getRelRef() override {return RelRef::FOLLOWS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_FOLLOWSCLAUSEEVALUATOR_H
