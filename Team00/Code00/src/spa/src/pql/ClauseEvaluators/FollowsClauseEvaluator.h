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
        RelRef getRelRef() override {return RelRef::FOLLOWS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
};


#endif //SPA_FOLLOWSCLAUSEEVALUATOR_H
