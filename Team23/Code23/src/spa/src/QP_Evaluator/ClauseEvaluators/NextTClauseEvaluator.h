//
// Created by Tin Hong Wen on 10/3/22.
//

#ifndef SPA_NEXTTCLAUSEEVALUATOR_H
#define SPA_NEXTTCLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

class NextTClauseEvaluator: public SuchThatClauseEvaluator {
public:
    NextTClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::NEXT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_NEXTTCLAUSEEVALUATOR_H
