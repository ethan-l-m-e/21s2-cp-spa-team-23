//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::list<std::string> QueryEvaluator::evaluate(Query* query) {
    // Initialise an empty result
    auto* synonymRelations = new SynonymRelations();
/*
    // Create ClauseEvaluators and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(PatternClause clause : query->getPatternClauses()) {
            PatternClauseEvaluator patternClauseEvaluator = PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator.evaluateClause();
            if (!patternResult.resultBoolean) return convertResultToString(result, query->getSelectedSynonym());
            result = mergeResults(result, patternResult);
        }
    }

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(SuchThatClause clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator.evaluateClause();
            if (!suchThatResult.resultBoolean) return convertResultToString(result, query->getSelectedSynonym());
            result = mergeResults(result, suchThatResult);
        }
    }
        */

    if (synonymRelations->isEmpty()) {
        auto* selectClauseEvaluator = new SelectClauseEvaluator(synonymRelations, pkb, query);
        Result result1 = selectClauseEvaluator->evaluateClause();
        return convertResultToStringList(result1, query->getSelectedSynonym());
    }

    return list<string>{"hello"};
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

std::list<std::string> QueryEvaluator::convertResultToStringList(Result result, string selectedSynonym) {

    //TODO: convert result object to output result string
    std::list<std::string> stringList;
    string* str  = std::get_if<std::string>(&result.resultHeader);
    if ((*str) == selectedSynonym) {
        vector<ResultItem> vec = result.resultItemList;
        std::string s;
        for(size_t i = 0; i < vec.size(); ++i)
        {
            s = std::get<std::string>(vec[i]);
            stringList.emplace_back(s);
        }
        return stringList;
    } else {
        return stringList;
    }
}

