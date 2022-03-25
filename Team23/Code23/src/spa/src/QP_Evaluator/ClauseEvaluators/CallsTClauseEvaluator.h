//
// Created by Tianyi Wang on 25/3/22.
//

#ifndef SPA_CALLSTCLAUSEEVALUATOR_H
#define SPA_CALLSTCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

#include <utility>

class CallsTClauseEvaluator : public SuchThatClauseEvaluator {
public:
    CallsTClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::CALLS_T;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_CALLSTCLAUSEEVALUATOR_H
