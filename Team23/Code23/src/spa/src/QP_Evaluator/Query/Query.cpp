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

vector<SuchThatClause> Query::getSuchThatClauses(){
    return suchThatClauses;
}

vector<PatternClause> Query::getPatternClauses(){
    return patternClauses;
}

std::vector<WithClause> Query::getWithClauses(){
    return withClauses;
}

std::vector<Argument> Query::getSelectedSynonyms() {
    return selectedSynonyms;
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

void Query::setSynonyms(std::vector<Argument> synonyms) {
    this->selectedSynonyms = std::move(synonyms);
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

