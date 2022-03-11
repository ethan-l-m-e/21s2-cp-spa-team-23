//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/FollowsClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/PatternClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ResultClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/FollowsTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ModifiesSClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/UsesSClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ModifiesPClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/UsesPClauseEvaluator.h"

std::list<std::string> QueryEvaluator::evaluate(Query* query) {

    // Initialise an empty synonym relations for storing intermediate result
    auto* resultTable = new ResultTable();

    // Create ClauseEvaluators and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(const PatternClause& clause : query->getPatternClauses()) {
            auto patternClauseEvaluator = new PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            bool patternResult = patternClauseEvaluator->evaluateClause(resultTable);
            delete patternClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!patternResult) return {};
        }
    }

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(const SuchThatClause& clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            bool suchThatResult = suchThatClauseEvaluator->evaluateClause(resultTable);
            delete suchThatClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!suchThatResult) return {};
        }
    }

    // Evaluate select clause and output the result
    auto* resultClauseEvaluator = new ResultClauseEvaluator(pkb, query);
    bool result = resultClauseEvaluator->evaluateClause(resultTable);
    delete resultClauseEvaluator;
    if (!result) return {};
    std::list<std::string> output = generateResultString(resultTable);
    delete resultTable;
    return output;
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
            return new UsesPClauseEvaluator(clause.argList, pkb, query);
        case RelRef::MODIFIES_P:
            return new ModifiesPClauseEvaluator(clause.argList, pkb, query);
        default:
            throw qp::QPEvaluatorException("No valid clause evaluator is found for relationship type");
    }
}

/**
 * Generate result list from a result object.
 * @param result  an Result object from a select clause evaluator
 * @return  a list of strings representing the result items
 */
std::list<std::string> QueryEvaluator::generateResultString(ResultTable* resultTable) {
    std::unordered_set<std::string> stringSet;

    if (resultTable->isBoolean()) {
        stringSet.insert(resultTable->getBooleanResult());
    } else if (!resultTable->isEmpty()) {
        for(int i = 0; i < resultTable->getTableSize(); i++) {
            std::string s;
            for (auto &col: *resultTable->getList()) {
                if (!s.empty()) s += " ";
                s += col[i];
            }
            stringSet.insert(s);
        }
    }
    return std::list<std::string> {std::begin(stringSet), std::end(stringSet)};
}

