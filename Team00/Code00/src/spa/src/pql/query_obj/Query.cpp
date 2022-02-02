//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

std::string Query::generateResult(PKB *pkb) {
    Result suchThatResults = suchThatClause.evaluateClause();
    Result patternResults = patternClause.evaluateClause();

    // Combine results and return
    std::string result; // remove later
    return result;
}

optional<DesignEntity> Query::findEntityType(std::string synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
    return std::nullopt;
    else
    return got->second;
}
