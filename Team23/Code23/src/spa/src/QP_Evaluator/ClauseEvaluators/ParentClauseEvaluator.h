//
// Created by Tianyi Wang on 11/2/22.
//

#ifndef SPA_PARENTCLAUSEEVALUATOR_H
#define SPA_PARENTCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class ParentClauseEvaluator : public SuchThatClauseEvaluator {
public:
    ParentClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_PARENTCLAUSEEVALUATOR_H
