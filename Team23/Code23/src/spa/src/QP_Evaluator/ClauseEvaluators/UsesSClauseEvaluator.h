//
// Created by Tianyi Wang on 17/2/22.
//

#ifndef SPA_USESSCLAUSEEVALUATOR_H
#define SPA_USESSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class UsesSClauseEvaluator : public SuchThatClauseEvaluator {
public:
    UsesSClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_USESSCLAUSEEVALUATOR_H
