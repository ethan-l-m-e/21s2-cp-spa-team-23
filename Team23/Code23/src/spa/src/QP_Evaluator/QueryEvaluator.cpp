//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QueryOptimizer.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluatorCollection.h"

/**
 * Evalute a query object, it evaluate the optimizeQueryClauses for each group and returns the result from evaluation.
 * @param queryObj the query object with synonym declarations and optimizeQueryClauses
 * @return a list of string values as the results for the query
 */
list<string> QueryEvaluator::evaluate(Query* queryObj) {

    query = queryObj;

    // perform optimization on the query
    auto *optimizer = new QueryOptimizer(query);
    optimizer->optimizeQueryClauses();

    // generate result tables for each group and store them in a map
    unordered_map<int, ResultTable *> groupedResultTables;
    for (const auto &group: *optimizer->getGroups()) {
        groupedResultTables.insert(std::make_pair(group, new ResultTable()));
    }

    // evaluate each clause in a loop
    bool isFalse = false;

    for (GroupedClause gc: *optimizer->getClauses()) {
        bool result;
        if (dynamic_cast<WithClause *>(gc.clause)) {
            // Create ClauseEvaluators and evaluate each with clause, merge the result to the corresponding result table
            auto *withClause = dynamic_cast<WithClause *>(gc.clause);
            auto withClauseEvaluator = new WithClauseEvaluator(query->getDeclarations(), withClause, pkb);
            result = withClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete withClauseEvaluator;

        } else if (dynamic_cast<SuchThatClause *>(gc.clause)) {
            // Create ClauseEvaluators and evaluate each suchThat clause, merge the result to the corresponding result table
            auto *suchThatClause = dynamic_cast<SuchThatClause *>(gc.clause);
            auto suchThatClauseEvaluator = generateEvaluator(*suchThatClause, *query->getDeclarations());
            result = suchThatClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete suchThatClauseEvaluator;

        } else if (dynamic_cast<PatternClause *>(gc.clause)) {
            // Create ClauseEvaluators and evaluate each pattern clause, merge the result to the corresponding result table
            auto *patternClause = dynamic_cast<PatternClause *>(gc.clause);
            auto patternClauseEvaluator = new PatternClauseEvaluator(query->getDeclarations(), patternClause, pkb);
            result = patternClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete patternClauseEvaluator;

        } else {
            throw qp::QPEvaluatorException("Invalid clause type");
        }
        // if the clause evaluates to false, terminate evaluation early.
        if (!result) {
            isFalse = true;
            break;
        }
    }

    auto *finalResultTable = new ResultTable();

    mergeToFinalResultTable(finalResultTable, groupedResultTables, isFalse);

    // Evaluate result clause
    auto *resultClauseEvaluator = new ResultClauseEvaluator(query->getDeclarations(), query->getResultClause(), pkb);
    bool result = resultClauseEvaluator->evaluateClause(finalResultTable);
    delete resultClauseEvaluator;
    if (!result) return {};
    list<string> output = generateResultString(finalResultTable);

    //deallocate memory for result tables and clear cache
    delete finalResultTable;
    for (auto map: groupedResultTables) delete map.second;
    delete optimizer;

    Cache::getInstance()->clearCache();

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
        for (int i = 0; i < resultTable->getTableHeight(); i++) {
            string s;
            for (auto col: resultTable->getProjection()) {
                if (!s.empty()) s += " ";
                s += (*resultTable->getList())[col][i];
            }
            stringSet.insert(s);
        }
    }
    return list<string>{std::begin(stringSet), std::end(stringSet)};
}

unordered_set<string> QueryEvaluator::getSelectedSynonyms() {

    unordered_set<string> selectedSynonyms;

    // examine the result clause and retrieve selected synonyms
    for (Argument synonym: query->getResultClause()->argList) {
        if (synonym.argumentType == ArgumentType::ATTR_REF) {
            auto attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
            selectedSynonyms.insert(attrRef.first);
        } else if (synonym.argumentType == ArgumentType::SYNONYM) {
            selectedSynonyms.insert(std::get<string>(synonym.argumentValue));
        } else if (synonym.argumentType == ArgumentType::BOOLEAN) {
            break;
        }
    }

    return selectedSynonyms;
}

/**
 * Merge result from individual result tables to the final result table.
 * @param finalResultTable the result table which contains information that will be used in the final output
 * @param groupedResultTables the mapping of group number to result tables for each group
 * @param isFalse boolean value that indicate whether the query is false
 */
void QueryEvaluator::mergeToFinalResultTable(ResultTable* finalResultTable, unordered_map<int, ResultTable*>& groupedResultTables, bool isFalse) {

    unordered_set<string> selectedSynonyms = getSelectedSynonyms();

    //set boolean result for false result
    if (isFalse) {
        finalResultTable->setBooleanResult(false);
        return;
    }


    // otherwise, populate the result table by selecting relevant columns from each group
    if (!selectedSynonyms.empty()) {

        // for queries with only 1 group, set the content of the result table to the final result table
        if (groupedResultTables.size() == 1) {
            finalResultTable->setResultTable(
                    *(groupedResultTables.begin())->second->getHeader(),
                    *(groupedResultTables.begin())->second->getList()
            );
            return;
        }

        // otherwise, for each result table, extract the relevant columns to the final result table
        for (auto map: groupedResultTables) {
            auto synonymList = map.second->getHeader();
            unordered_set<string> synonyms(synonymList->begin(), synonymList->end());
            vector<vector<string>> selectedColumns;
            vector<string> selectedSynonymHeaders;
            for (auto synonym: selectedSynonyms) {
                if (synonyms.find(synonym) != synonyms.end()) {
                    auto column = map.second->getColumn(synonym);
                    selectedColumns.emplace_back(*column);
                    selectedSynonymHeaders.emplace_back(synonym);
                }
            }
            // if there are selected columns from the group, merge selected columns to the final result table
            if (!selectedColumns.empty())
                finalResultTable->mergeColumnsToTable(selectedColumns, selectedSynonymHeaders);

        }
    }
}
