//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

std::string Query::generateResult(
        PKB *pkb,
        unordered_map<string, DesignEntity> declarations) {
    Result suchThatResults = suchThatClause.evaluateClause(pkb, declarations);
    Result patternResults = patternClause.evaluateClause(pkb, declarations);

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
