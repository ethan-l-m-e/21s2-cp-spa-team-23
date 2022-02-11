//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_SUCHTHATCLAUSEEVALUATOR_H
#define SPA_SUCHTHATCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

enum class ClauseSynonymType {
    SYNONYM_NONE,
    SYNONYM_LEFT,
    SYNONYM_RIGHT,
    SYNONYM_BOTH
};

class SuchThatClauseEvaluator : public ClauseEvaluator {
protected:
    SuchThatClauseEvaluator(std::vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {};

    Result evaluateClause() override;
    virtual bool isRelation(std::string left, std::string right) = 0;
    virtual unordered_set<std::string> getLeftSynonymValue(std::string right) = 0;
    virtual unordered_set<std::string> getRightSynonymValue(std::string left) = 0;
    virtual RelRef getRelRef() = 0;

    vector<ResultItem> generateTuples(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet);
    vector<ResultItem> convertSetToVector(unordered_set<string> set);
    unordered_set<string> findIntersection(unordered_set<string> set1, unordered_set<string> set2);

    ClauseSynonymType getClauseSynonymType();
    void evaluateNoSynonym();
    void evaluateTwoSynonyms();
    void evaluateLeftSynonym();
    void evaluateRightSynonym();

    Argument argLeft = argList[0];
    Argument argRight = argList[1];


};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
