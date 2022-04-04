//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QueryOptimizer.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluatorCollection.h"

list<string> QueryEvaluator::evaluate(Query* query) {

    // Initialise an empty synonym relations for storing intermediate result
    auto* resultTable = new ResultTable();

    auto* optimizer = new QueryOptimizer(query);
    optimizer->groupClauses();
    std::vector<Clause*> clauses = optimizer->getClauses();

    for (Clause* clause : clauses) {
        if (dynamic_cast<WithClause*>(clause)) {
            // Create ClauseEvaluators and evaluate each with clause
            auto* withClause = dynamic_cast<WithClause*>(clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto withClauseEvaluator = new WithClauseEvaluator(query->getDeclarations(), withClause, pkb);
            bool withResult = withClauseEvaluator->evaluateClause(resultTable);
            delete withClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!withResult) break;
        }
        else if (dynamic_cast<SuchThatClause*>(clause)){
            // Create ClauseEvaluators and evaluate each suchThat clause
            auto* suchThatClause = dynamic_cast<SuchThatClause *>(clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto suchThatClauseEvaluator = generateEvaluator(*suchThatClause, *query->getDeclarations());
            bool suchThatResult = suchThatClauseEvaluator->evaluateClause(resultTable);
            delete suchThatClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!suchThatResult) break;
        }
        else if (dynamic_cast<PatternClause*>(clause)){
            // Create ClauseEvaluators and evaluate each pattern clause
            auto* patternClause = dynamic_cast<PatternClause *>(clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto patternClauseEvaluator = new PatternClauseEvaluator(query->getDeclarations(), patternClause, pkb);
            bool patternResult = patternClauseEvaluator->evaluateClause(resultTable);
            delete patternClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation early.
            if (!patternResult) break;
        }
    }

    delete optimizer;

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
ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause& clause, unordered_map<string, DesignEntity>& declarations) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new TableClauseEvaluator<OneToOneRelationship>(&declarations, &clause, pkb, &pkb->relationship.follows);
        case RelRef::PARENT:
            return new TableClauseEvaluator<OneToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.parent);
        case RelRef::FOLLOWS_T:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.followsT);
        case RelRef::PARENT_T:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.parentT);
        case RelRef::USES_S:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.usesS);
        case RelRef::MODIFIES_S:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.modifiesS);
        case RelRef::USES_P:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.usesP);
        case RelRef::MODIFIES_P:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.modifiesP);
        case RelRef::CALLS:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.calls);
        case RelRef::CALLS_T:
            return new TableClauseEvaluator<ManyToManyRelationship>(&declarations, &clause, pkb, &pkb->relationship.callsT);
        case RelRef::NEXT:
            return new TableClauseEvaluator<NextRelationship>(&declarations, &clause, pkb, &pkb->relationship.next);
        case RelRef::NEXT_T:
            return new NextTClauseEvaluator(&declarations, &clause, pkb);
        case RelRef::AFFECTS:
            return new AffectsClauseEvaluator(&declarations, &clause, pkb);
        case RelRef::AFFECTS_T:
            return new AffectsTClauseEvaluator(&declarations, &clause, pkb);

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
            for (auto col: resultTable->getProjection()) {
                if (!s.empty()) s += " ";
                s += (*resultTable->getList())[col][i];
            }
            stringSet.insert(s);
        }
    }
    return list<string> {std::begin(stringSet), std::end(stringSet)};
}

