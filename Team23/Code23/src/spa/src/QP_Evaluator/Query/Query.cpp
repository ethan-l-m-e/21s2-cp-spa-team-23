//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

bool Query::hasSuchThatClause(){
    return !suchThatClauses.empty();
}

bool Query::hasPatternClause(){
    return !patternClauses.empty();
}

bool Query::hasWithClause(){
    return !withClauses.empty();
}

unordered_map<string, DesignEntity>* Query::getDeclarations(){
    return &declarations;
}


vector<SuchThatClause>* Query::getSuchThatClauses(){
    return &suchThatClauses;
}

vector<PatternClause>* Query::getPatternClauses(){
    return &patternClauses;
}

std::vector<WithClause>* Query::getWithClauses(){
    return &withClauses;
}

ResultClause* Query::getResultClause() {
    return &resultClause;
}

DesignEntity Query::getSynonymType(std::string synonym) {
    return declarations.find(synonym)->second;
}

DesignEntity Query::findEntityType(const std::string& synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
        return DesignEntity::EMPTY;
    else
        return got->second;
}

void Query::setDeclarations(unordered_map<string, DesignEntity> declarationsMap) {
    this->declarations = std::move(declarationsMap);
}

void Query::setResultClause(ResultClause clause) {
    this->resultClause = std::move(clause);
}

void Query::setSuchThatClauses(vector<SuchThatClause> clauses) {
    this->suchThatClauses = std::move(clauses);
}

void Query::setPatternClauses(vector<PatternClause> clauses) {
    this->patternClauses = std::move(clauses);
}

void Query::setWithClauses(vector<WithClause> clauses) {
    this->withClauses = std::move(clauses);
}

