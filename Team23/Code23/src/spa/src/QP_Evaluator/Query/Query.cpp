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

std::vector<string> Query::getSelectedSynonym() {
    return selectedSynonyms;
}

std::vector<DesignEntity> Query::getSelectedSynonymTypes() {
    std::vector<DesignEntity> designEntities;
    for(const string& selectedSynonym : selectedSynonyms){
        designEntities.emplace_back(declarations.find(selectedSynonym)->second);
    }
    return designEntities;
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

void Query::setSynonyms(std::vector<std::string> synonyms) {
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


/*
optional<DesignEntity> findEntityType(std::string synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
        return std::nullopt;
    else
        return got->second;
}
 */

