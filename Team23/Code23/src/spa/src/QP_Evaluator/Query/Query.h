//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <unordered_map>
#include "PKB.h"
#include "Clause.h"

enum class DesignEntity{
    EMPTY,
    PROCEDURE,
    STMT,
    READ,
    PRINT,
    ASSIGN,
    CALL,
    WHILE,
    IF,
    VARIABLE,
    CONSTANT
};

class Query {
protected:
    unordered_map<string, DesignEntity> declarations;
    vector<SuchThatClause> suchThatClauses;
    vector<PatternClause> patternClauses;
    vector<WithClause> withClauses;
    vector<string> selectedSynonyms;
public:
    bool hasSuchThatClause();
    bool hasPatternClause();
    vector<PatternClause> getPatternClauses();
    vector<SuchThatClause> getSuchThatClauses();
    vector<string> getSelectedSynonym();
    vector<DesignEntity> getSelectedSynonymTypes();
    DesignEntity findEntityType(const std::string&);
    void setDeclarations(unordered_map<string, DesignEntity>);
    void setSynonyms(vector<std::string>);
    void setSuchThatClauses(vector<SuchThatClause>);
    void setPatternClauses(vector<PatternClause>);
    void setWithClauses(vector<WithClause>);
};

#endif //SPA_QUERY_H
