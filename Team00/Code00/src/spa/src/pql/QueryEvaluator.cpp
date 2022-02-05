//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::string QueryEvaluator::evaluate(Query* query) {
    return query->generateResult(pkb);
    Result result;
    if(query->hasPatternClause()) {
        for(PatternClause clause : query->getPatternClauses()) {
            ClauseEvaluator* patternClauseEvaluator = new PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResults = patternClauseEvaluator->evaluateClause();
        }
    }

    if(query->hasSuchThatClause()) {
        for(SuchThatClause clause : query->getSuchThatClauses()) {
            ClauseEvaluator* suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResults = suchThatClauseEvaluator->evaluateClause();
        }
    }

    return;
}

ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::FOLLOWS_T:
            // return followsTClauseEvaluator();
            break;
        case RelRef::PARENT:
            // return parentClauseEvaluator();
            break;
        case RelRef::PARENT_T:
            // return parentTTClauseEvaluator();
            break;
        case RelRef::USES_S:
            // return usesSClauseEvaluator();
            break;
        case RelRef::USES_P:
            // return usesPClauseEvaluator();
            break;
        case RelRef::MODIFIES_S:
            // return modifiesSClauseEvaluator();
            break;
        case RelRef::MODIFIES_P:
            // return modifiesPClauseEvaluator();
            break;
    }
}

