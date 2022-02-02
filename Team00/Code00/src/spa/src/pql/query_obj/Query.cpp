//
// Created by リム・イーサン on 30/1/22.
//

#include "Query.h"

std::string Query::generateResult(
        PKB *pkb) {
    Result suchThatResults = suchThatClause.evaluateClause(pkb, declarations);
    Result patternResults = patternClause.evaluateClause(pkb, declarations);

    // Combine results and return
    std::string result; // remove later
    return result;
}
