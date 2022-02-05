//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::string QueryEvaluator::evaluate(Query* query) {
    // Initialise an empty result
    Result result;

    // Create evaluator and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(PatternClause clause : query->getPatternClauses()) {
            ClauseEvaluator* patternClauseEvaluator = new PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator->evaluateClause();
            result = mergeResults(result, patternResult);
        }
    }

    // Create evaluator and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(SuchThatClause clause : query->getSuchThatClauses()) {
            ClauseEvaluator* suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator->evaluateClause();
            result = mergeResults(result, suchThatResult);
        }
    }

    if (result.resultType == ResultType::EMPTY) {
        DesignEntity entityType = query->getSelectedSynonymType();
        //TODO: Evaluate clause without suchThat and pattern
        //pkb->getAllType(entityType);
        // merge result
    }

    return convertResultToString(result);
}

ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::FOLLOWS_T:
            // return followsTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT:
            // return parentClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT_T:
            // return parentTTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_S:
            // return usesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_P:
            // return usesPClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_S:
            // return modifiesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_P:
            // return modifiesPClauseEvaluator(clause.argList, pkb, query);
            break;
    }
}

Result QueryEvaluator::mergeResults(Result r1, Result r2) {
    return r1;
}

std::string QueryEvaluator::convertResultToString(Result result) {
    return "resultString"
}

