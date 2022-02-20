//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

#include <utility>

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

std::string Query::getSelectedSynonym() {
    return selectedSynonym;
}

DesignEntity Query::getSelectedSynonymType() {
    return declarations.find(selectedSynonym)->second;
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

void Query::setSynonym(std::string synonym) {
    this->selectedSynonym = std::move(synonym);
}

void Query::setSuchThatClauses(vector<SuchThatClause> clauses) {
    this->suchThatClauses = std::move(clauses);
}

void Query::setPatternClauses(vector<PatternClause> clauses) {
    this->patternClauses = std::move(clauses);
}


/*
optional<DesignEntity> findEntityType(std::string synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
        return std::nullopt;
    else
        return got->second;
}
 */

