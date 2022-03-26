//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluatorCollection.h"

list<string> QueryEvaluator::evaluate(Query* query) {

    // Initialise an empty synonym relations for storing intermediate result
    auto* resultTable = new ResultTable();

    // Create ClauseEvaluators and evaluate each pattern clause
    if(query->hasPatternClause() && resultTable->getBooleanResult()) {
        for(PatternClause& clause : *query->getPatternClauses()) {
            auto patternClauseEvaluator = new PatternClauseEvaluator(query->getDeclarations(), &clause, pkb);
            bool patternResult = patternClauseEvaluator->evaluateClause(resultTable);
            delete patternClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation early.
            if (!patternResult) break;
        }
    }

    // Create ClauseEvaluators and evaluate each suchThat clause
    if(query->hasSuchThatClause() && resultTable->getBooleanResult()) {
        for(SuchThatClause& clause : *query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, *query);
            bool suchThatResult = suchThatClauseEvaluator->evaluateClause(resultTable);
            delete suchThatClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!suchThatResult) break;
        }
    }

    // Create ClauseEvaluators and evaluate each with clause
    if(query->hasWithClause() && resultTable->getBooleanResult()) {
        for(WithClause& clause : query->getWithClauses()) {
            auto withClauseEvaluator = new WithClauseEvaluator(query->getDeclarations(), &clause, pkb);
            bool withResult = withClauseEvaluator->evaluateClause(resultTable);
            delete withClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!withResult) break;
        }
    }

    // Evaluate result clause and output the result
    auto* resultClauseEvaluator = new ResultClauseEvaluator(query->getDeclarations(), query->getResultClause(), pkb);
    bool result = resultClauseEvaluator->evaluateClause(resultTable);
    delete resultClauseEvaluator;
    if (!result) return {};
    list<string> output = generateResultString(resultTable);
    delete resultTable;
    return output;
}

/**
 * Generate a clause evaluator from an such that clause based on the relationship type.
 * @param clause  a reference to an SuchThatClause object
 * @param query  a Query object pointer
 * @return  a pointer for the generated ClauseEvaluator.
 */
ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause& clause, Query& query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::PARENT:
            return new ParentClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::FOLLOWS_T:
            return new FollowsTClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::PARENT_T:
            return new ParentTClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::USES_S:
            return new UsesSClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::MODIFIES_S:
            return new ModifiesSClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::USES_P:
            return new UsesPClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::MODIFIES_P:
            return new ModifiesPClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::NEXT:
            return new NextClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::NEXT_T:
            return new NextTClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::CALLS:
            return new CallsClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::CALLS_T:
            return new CallsTClauseEvaluator(query.getDeclarations(), &clause, pkb);
        case RelRef::AFFECTS:
            return new AffectsClauseEvaluator(query.getDeclarations(), &clause, pkb);
       default:
            throw qp::QPEvaluatorException("No valid clause evaluator is found for relationship type");
    }
}

/**
 * Generate result list from a result table.
 * @param result  an ResultTable containing the final result
 * @return  a list of strings representing the result items
 */
list<string> QueryEvaluator::generateResultString(ResultTable* resultTable) {
    std::unordered_set<string> stringSet;

    if (resultTable->isBoolean()) {
        stringSet.insert(resultTable->getBooleanResultString());
    } else if (!resultTable->isEmpty()) {
        for(int i = 0; i < resultTable->getTableHeight(); i++) {
            string s;
            for (auto &col: *resultTable->getList()) {
                if (!s.empty()) s += " ";
                s += col[i];
            }
            stringSet.insert(s);
        }
    }
    return list<string> {std::begin(stringSet), std::end(stringSet)};
}

