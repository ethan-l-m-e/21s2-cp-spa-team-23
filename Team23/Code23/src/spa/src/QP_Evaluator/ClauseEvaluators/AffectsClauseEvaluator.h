//
// Created by Tin Hong Wen on 16/3/22.
//

#ifndef SPA_AFFECTSCLAUSEEVALUATOR_H
#define SPA_AFFECTSCLAUSEEVALUATOR_H


#include "CacheClauseEvaluator.h"
#include "QP_database/AffectsOperator.h"

class AffectsClauseEvaluator: public CacheClauseEvaluator {
public:
    AffectsClauseEvaluator (vector<Argument> args, PKB* pkb, Query* query) : CacheClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::AFFECTS;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
    AffectsOperator* affectsOperator = AffectsOperator::getInstance();

};


#endif //SPA_AFFECTSCLAUSEEVALUATOR_H
