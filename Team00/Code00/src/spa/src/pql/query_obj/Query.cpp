//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

std::string Query::generateResult(
        PKB *pkb) {
    // Combine results and return
    std::string result; // remove later
    return result;
}

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

DesignEntity Query::findEntityType(std::string synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
        return DesignEntity::EMPTY;
    else
        return got->second;
}

void Query::setDeclarations(unordered_map<string, DesignEntity> declarationsMap) {
    declarations = declarationsMap;
}

void Query::setSynonym(std::string synonym) {
    selectedSynonym = synonym;
}

void Query::addSuchThatClause(SuchThatClause suchThatClause) {
    suchThatClauses.emplace_back(suchThatClause);
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

