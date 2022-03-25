//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "Clause.h"

#include <unordered_map>
#include <variant>
#include <vector>

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

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
    vector<Argument> selectedSynonyms;
public:
    bool hasSuchThatClause();
    bool hasPatternClause();
    unordered_map<string, DesignEntity>* getDeclarations();
    vector<PatternClause> getPatternClauses();
    vector<SuchThatClause> getSuchThatClauses();
    vector<WithClause> getWithClauses();
    vector<Argument> getSelectedSynonyms();
    DesignEntity getSynonymType(string synonym);
    DesignEntity findEntityType(const string&);
    void setDeclarations(unordered_map<string, DesignEntity>);
    void setSynonyms(vector<Argument>);
    void setSuchThatClauses(vector<SuchThatClause>);
    void setPatternClauses(vector<PatternClause>);
    void setWithClauses(vector<WithClause>);
};

#endif //SPA_QUERY_H
