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
public:
    SuchThatClauseEvaluator(vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {};
    bool evaluateClause(ResultTable* resultTable) override;
protected:
    virtual bool isRelation(string left, string right) = 0;
    virtual unordered_set<string> getLeftSynonymValue(string right) = 0;
    virtual unordered_set<string> getRightSynonymValue(string left) = 0;
    virtual pair<DesignEntity, DesignEntity> getWildcardType() = 0;
    virtual RelRef getRelRef() = 0;

    unordered_set<std::pair<string, string>> generateTuples(unordered_set<string>&, unordered_set<string>&, bool);
    bool validateRelation(unordered_set<string>&, unordered_set<string>&);
    unordered_set<string> generateLeftSet (unordered_set<string>&);
    unordered_set<string> generateRightSet (unordered_set<string>&);
    void filterByType (unordered_set<string>&, DesignEntity);
    bool isEntityType (const string&, DesignEntity);
    unordered_set<string> generateValueSet(Argument&, DesignEntity);

    [[nodiscard]] ClauseSynonymType getClauseSynonymType() const;
    void evaluateNoSynonym();
    void evaluateTwoSynonyms();
    void evaluateLeftSynonym();
    void evaluateRightSynonym();

    Argument argLeft = argList[0];
    Argument argRight = argList[1];

};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
