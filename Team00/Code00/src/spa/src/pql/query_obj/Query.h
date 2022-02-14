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
    std::string selectedSynonym;
public:
    virtual std::string generateResult(PKB* pkb);
    bool hasSuchThatClause();
    bool hasPatternClause();
    vector<PatternClause> getPatternClauses();
    vector<SuchThatClause> getSuchThatClauses();
    std::string getSelectedSynonym();
    DesignEntity getSelectedSynonymType();
    DesignEntity findEntityType(std::string synonym);
    void setDeclarations(unordered_map<string, DesignEntity>);
    void setSynonym(std::string);

    void addSuchThatClause(SuchThatClause suchThatClause);
};

#endif //SPA_QUERY_H
