//
// Created by Tianyi Wang on 17/2/22.
//

#ifndef SPA_PARENTTCLAUSEEVALUATOR_H
#define SPA_PARENTTCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

class ParentTClauseEvaluator : public SuchThatClauseEvaluator {
public:
    ParentTClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::FOLLOWS_T;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};

#endif //SPA_PARENTTCLAUSEEVALUATOR_H
