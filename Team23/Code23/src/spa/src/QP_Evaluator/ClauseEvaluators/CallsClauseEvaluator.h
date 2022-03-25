//
// Created by Tianyi Wang on 25/3/22.
//

#ifndef SPA_CALLSCLAUSEEVALUATOR_H
#define SPA_CALLSCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class CallsClauseEvaluator : public SuchThatClauseEvaluator {
public:
    CallsClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::CALLS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_CALLSCLAUSEEVALUATOR_H
