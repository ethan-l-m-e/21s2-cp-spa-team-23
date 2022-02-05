//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"

std::string QueryEvaluator::evaluate(Query* query) {
    return query->generateResult(pkb);
    Result result;

    if(query->hasPatternClause()) {
        for(auto clause : query->getPatternClauses()) {
            Result patternResults = patternClauseEvaluator.evaluateClause(pkb, query);
        }

    }

    if(query->hasSuchThatClause()) {
        for(auto clause : query->getSuchThatClauses()) {
            Result suchThatResults = suchThatClauseEvaluator.evaluateClause(pkb, query);
        }
    }

    return;
}
