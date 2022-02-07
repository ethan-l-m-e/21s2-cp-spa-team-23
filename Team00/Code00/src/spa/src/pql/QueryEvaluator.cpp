//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::string QueryEvaluator::evaluate(Query* query) {
    // Initialise an empty result
    Result result = {ResultType::EMPTY};
/*
    // Create evaluator and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(PatternClause clause : query->getPatternClauses()) {
            PatternClauseEvaluator patternClauseEvaluator = PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator.evaluateClause();
            if (!patternResult.resultBoolean) return convertResultToString(result, query->getSelectedSynonym());
            result = mergeResults(result, patternResult);
        }
    }

    // Create evaluator and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(SuchThatClause clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator.evaluateClause();
            if (!suchThatResult.resultBoolean) return convertResultToString(result, query->getSelectedSynonym());
            result = mergeResults(result, suchThatResult);
        }
    }
        */

    if (result.resultType == ResultType::EMPTY) {
        SelectClauseEvaluator* selectClauseEvaluator = new SelectClauseEvaluator(&result, pkb, query);
        Result result1 = selectClauseEvaluator->evaluateClause();
        return convertResultToString(result1, query->getSelectedSynonym());
    }

    return convertResultToString(result, query->getSelectedSynonym());
}

ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
            break;
        /*
        case RelRef::FOLLOWS_T:
            // return FollowsTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT:
            // return ParentClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT_T:
            // return ParentTTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_S:
            // return UsesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_P:
            // return UsesPClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_S:
            // return ModifiesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_P:
            // return ModifiesPClauseEvaluator(clause.argList, pkb, query);
            break;
        */
        default:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
    }
}

Result QueryEvaluator::mergeResults(Result r1, Result r2) {
    //TODO: method for merging two results
    return r1;
}

std::string QueryEvaluator::convertResultToString(Result result, string selectedSynonym) {

    //TODO: convert result object to output result string
    string* str  = std::get_if<std::string>(&result.resultHeader);
    if ((*str) == selectedSynonym) {
        vector<ResultItem> vec = result.resultItemList;
        std::stringstream ss;
        for(size_t i = 0; i < vec.size(); ++i)
        {
            if(i != 0)
                ss << " ";
            ss << std::get<std::string>(vec[i]);
        }
        return ss.str();
    } else {
        return "result";
    }
}

