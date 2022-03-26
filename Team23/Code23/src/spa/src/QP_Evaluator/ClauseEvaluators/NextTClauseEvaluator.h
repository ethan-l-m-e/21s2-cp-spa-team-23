//
// Created by Tin Hong Wen on 10/3/22.
//

#ifndef SPA_NEXTTCLAUSEEVALUATOR_H
#define SPA_NEXTTCLAUSEEVALUATOR_H

#include "CacheClauseEvaluator.h"
#include "QP_database/NextTOperator.h"

class NextTClauseEvaluator: public CacheClauseEvaluator {
public:
    NextTClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): CacheClauseEvaluator(declarations, clause, pkb) {}
    RelRef getRelRef() override {return RelRef::NEXT_T;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
    NextTOperator* nextTOperator = NextTOperator::getInstance();
};


#endif //SPA_NEXTTCLAUSEEVALUATOR_H
