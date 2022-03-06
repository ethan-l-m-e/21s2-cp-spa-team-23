//
// Created by Tianyi Wang on 6/3/22.
//

#ifndef SPA_USESPCLAUSEEVALUATOR_H
#define SPA_USESPCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class UsesPClauseEvaluator : public SuchThatClauseEvaluator {
public:
    UsesPClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_USESPCLAUSEEVALUATOR_H
