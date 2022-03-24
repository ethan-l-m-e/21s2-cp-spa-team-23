//
// Created by Tianyi Wang on 25/3/22.
//

#ifndef SPA_CALLSCLAUSEEVALUATOR_H
#define SPA_CALLSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class CallsClauseEvaluator : public SuchThatClauseEvaluator {
public:
    CallsClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::CALLS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_CALLSCLAUSEEVALUATOR_H
