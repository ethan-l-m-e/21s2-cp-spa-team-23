//
// Created by Tin Hong Wen on 10/3/22.
//

#ifndef SPA_NEXTCLAUSEEVALUATOR_H
#define SPA_NEXTCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class NextClauseEvaluator: public SuchThatClauseEvaluator {
public:
    NextClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::NEXT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_NEXTCLAUSEEVALUATOR_H
