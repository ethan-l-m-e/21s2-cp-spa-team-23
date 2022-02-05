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

vector<Clause> Query::getSuchThatClauses(){
    return suchThatClauses;
}

vector<Clause> Query::getPatternClauses(){
    return patternClauses;
}

