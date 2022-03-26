//
// Created by Tianyi Wang on 25/3/22.
//

#ifndef SPA_CALLSTCLAUSEEVALUATOR_H
#define SPA_CALLSTCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class CallsTClauseEvaluator : public SuchThatClauseEvaluator {
public:
    CallsTClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::CALLS_T;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_CALLSTCLAUSEEVALUATOR_H
