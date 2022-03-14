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
    SuchThatClauseEvaluator(std::vector<Argument> args, PKB* pkb, Query* query): ClauseEvaluator(std::move(args), pkb, query) {};
    bool evaluateClause(ResultTable* resultTable) override;
protected:
    virtual bool isRelation(std::string left, std::string right) = 0;
    virtual unordered_set<std::string> getLeftSynonymValue(std::string right) = 0;
    virtual unordered_set<std::string> getRightSynonymValue(std::string left) = 0;
    virtual pair<DesignEntity, DesignEntity> getWildcardType() = 0;
    virtual RelRef getRelRef() = 0;

    vector<ResultItem> generateTuples(unordered_set<std::string>&, unordered_set<std::string>&);
    bool validateRelation(unordered_set<std::string>&, unordered_set<std::string>&);
    unordered_set<std::string> generateLeftSet (unordered_set<std::string>&);
    unordered_set<std::string> generateRightSet (unordered_set<std::string>&);
    void filterByType (unordered_set<std::string>&, DesignEntity);
    bool isEntityType (const std::string&, DesignEntity);
    unordered_set<string> generateValueSet(Argument&, DesignEntity);
    static vector<ResultItem> convertSetToVector(unordered_set<std::string>);

    [[nodiscard]] ClauseSynonymType getClauseSynonymType() const;
    void evaluateNoSynonym();
    void evaluateTwoSynonyms();
    void evaluateLeftSynonym();
    void evaluateRightSynonym();

    Argument argLeft = argList[0];
    Argument argRight = argList[1];

};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
