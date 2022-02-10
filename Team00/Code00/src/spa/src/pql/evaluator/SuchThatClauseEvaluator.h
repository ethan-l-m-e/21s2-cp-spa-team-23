//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_SUCHTHATCLAUSEEVALUATOR_H
#define SPA_SUCHTHATCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SuchThatClauseEvaluator : public ClauseEvaluator {
protected:
    SuchThatClauseEvaluator(std::vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {};
    virtual std::vector<ResultItem> generateTuples(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet) = 0;
    virtual RelRef getRelRef() = 0;
    bool hasTwoSynonyms();
    bool hasNoSynonym();
    bool hasLeftSynonym();
    bool hasRightSynonym();
};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
