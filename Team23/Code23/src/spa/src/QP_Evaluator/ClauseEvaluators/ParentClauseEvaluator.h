//
// Created by Tianyi Wang on 11/2/22.
//

#ifndef SPA_PARENTCLAUSEEVALUATOR_H
#define SPA_PARENTCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class ParentClauseEvaluator : public SuchThatClauseEvaluator {
public:
    ParentClauseEvaluator (vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<string> getLeftSynonymValue(string right) override;
    unordered_set<string> getRightSynonymValue(string left) override;
    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_PARENTCLAUSEEVALUATOR_H
