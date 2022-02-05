//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <unordered_map>
#include "PKB.h"
#include "Clause.h"

enum class DesignEntity{
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
    vector<SuchThatClause> patternClauses;
    vector<PatternClause> suchThatClauses;
    std::string selectedSynonym;
public:
    virtual std::string generateResult(PKB* pkb);
    bool hasSuchThatClause();
    bool hasPatternClause();
    vector<SuchThatClause> getSuchThatClauses();
    vector<PatternClause> getPatternClauses();
};

#endif //SPA_QUERY_H
