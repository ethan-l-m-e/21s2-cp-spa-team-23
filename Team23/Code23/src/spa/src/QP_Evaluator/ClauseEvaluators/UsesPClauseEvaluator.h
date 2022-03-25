//
// Created by Tianyi Wang on 6/3/22.
//

#ifndef SPA_USESPCLAUSEEVALUATOR_H
#define SPA_USESPCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class UsesPClauseEvaluator : public SuchThatClauseEvaluator {
public:
    UsesPClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_USESPCLAUSEEVALUATOR_H
