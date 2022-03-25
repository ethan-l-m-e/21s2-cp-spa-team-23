//
// Created by Tin Hong Wen on 25/3/22.
//

#ifndef SPA_AFFECTSTCLAUSEEVALUATOR_H
#define SPA_AFFECTSTCLAUSEEVALUATOR_H

#include "CacheClauseEvaluator.h"
#include "QP_database/AffectsTOperator.h"

class AffectsTClauseEvaluator: public CacheClauseEvaluator {
public:
    AffectsTClauseEvaluator (vector<Argument> args, PKB* pkb, Query* query) : CacheClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::AFFECTS_T;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
    AffectsTOperator* affectsTOperator = AffectsTOperator::getInstance();
};


#endif //SPA_AFFECTSTCLAUSEEVALUATOR_H
