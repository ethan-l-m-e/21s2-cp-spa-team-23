//
// Created by Tin Hong Wen on 16/3/22.
//

#ifndef SPA_AFFECTSCLAUSEEVALUATOR_H
#define SPA_AFFECTSCLAUSEEVALUATOR_H


#include "CacheClauseEvaluator.h"
#include "QP_database/AffectsOperator.h"

class AffectsClauseEvaluator: public CacheClauseEvaluator {
public:
    AffectsClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): CacheClauseEvaluator(declarations, clause, pkb) {};
    RelRef getRelRef() override {return RelRef::AFFECTS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
    AffectsOperator* affectsOperator = AffectsOperator::getInstance();

};


#endif //SPA_AFFECTSCLAUSEEVALUATOR_H
