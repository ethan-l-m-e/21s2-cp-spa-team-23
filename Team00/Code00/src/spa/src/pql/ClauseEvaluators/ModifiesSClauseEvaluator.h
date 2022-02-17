//
// Created by Tianyi Wang on 17/2/22.
//

#ifndef SPA_MODIFIESSCLAUSEEVALUATOR_H
#define SPA_MODIFIESSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

class ModifiesSClauseEvaluator : public SuchThatClauseEvaluator {
public:
    ModifiesSClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_MODIFIESSCLAUSEEVALUATOR_H
