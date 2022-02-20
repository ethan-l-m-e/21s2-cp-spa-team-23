//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/FollowsClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/PatternClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/SelectClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/FollowsTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ModifiesSClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/UsesSClauseEvaluator.h"

std::list<std::string> QueryEvaluator::evaluate(Query* query) {

    // Initialise an empty synonym relations for storing intermediate result
    auto* synonymRelations = new SynonymRelations();

    // Create ClauseEvaluators and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(const PatternClause& clause : query->getPatternClauses()) {
            auto patternClauseEvaluator = new PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator->evaluateClause();
            delete patternClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!patternResult.resultBoolean) return {};
            synonymRelations->mergeResultToSynonymsRelations( patternResult);
        }
    }

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(const SuchThatClause& clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator->evaluateClause();
            delete suchThatClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!suchThatResult.resultBoolean) return {};
            synonymRelations->mergeResultToSynonymsRelations( suchThatResult);
        }
    }

    // Evaluate select clause and output the result
    auto* selectClauseEvaluator = new SelectClauseEvaluator(synonymRelations, pkb, query);
    Result selectResult = selectClauseEvaluator->evaluateClause();
    delete selectClauseEvaluator;
    delete synonymRelations;
    return generateResultString(selectResult);
}

/**
 * Generate a clause evaluator from an such that clause based on the relationship type.
 * @param clause  a reference to an SuchThatClause object
 * @param query  a Query object pointer
 * @return  a pointer for the generated ClauseEvaluator.
 */
ClauseEvaluator* QueryEvaluator::generateEvaluator(const SuchThatClause& clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
        case RelRef::PARENT:
            return new ParentClauseEvaluator(clause.argList, pkb, query);
        case RelRef::FOLLOWS_T:
            return new FollowsTClauseEvaluator(clause.argList, pkb, query);
        case RelRef::PARENT_T:
            return new ParentTClauseEvaluator(clause.argList, pkb, query);
        case RelRef::USES_S:
            return new UsesSClauseEvaluator(clause.argList, pkb, query);
        case RelRef::MODIFIES_S:
            return new ModifiesSClauseEvaluator(clause.argList, pkb, query);
        case RelRef::USES_P:
            // return new UsesPClauseEvaluator(clause.argList, pkb, query);
        case RelRef::MODIFIES_P:
            // return ModifiesPClauseEvaluator(clause.argList, pkb, query);
        default:
            throw qp::QPEvaluatorException("No valid clause evaluator is found for relationship type");
    }
}

/**
 * Generate result list from a result object.
 * @param result  an Result object from a select clause evaluator
 * @return  a list of strings representing the result items
 */
std::list<std::string> QueryEvaluator::generateResultString(Result& result) {
    std::list<std::string> stringList;

    if (result.resultType == ResultType::STRING && !result.resultItemList.empty()) {
        for (auto &resultItem: result.resultItemList) {
            auto s = std::get<std::string>(resultItem);
            stringList.emplace_back(s);
        }
    }
    return stringList;
}

