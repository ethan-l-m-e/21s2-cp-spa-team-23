//
// Created by Tianyi Wang on 11/2/22.
//

#ifndef SPA_PARENTCLAUSEEVALUATOR_H
#define SPA_PARENTCLAUSEEVALUATOR_H


#include "SuchThatClauseEvaluator.h"

#include <utility>

class ParentClauseEvaluator : public SuchThatClauseEvaluator {
public:
    ParentClauseEvaluator (std::vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {}
    RelRef getRelRef() override {return RelRef::PARENT;};
protected:
    bool isRelation(string left, string right) override;
    unordered_set<std::string> getLeftSynonymValue(std::string right) override;
    unordered_set<std::string> getRightSynonymValue(std::string left) override;
};


#endif //SPA_PARENTCLAUSEEVALUATOR_H
