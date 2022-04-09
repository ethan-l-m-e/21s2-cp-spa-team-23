//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"
#include "QueryOptimizer.h"
#include "QP_Parser/Exception.h"
#include "QP_Evaluator/ClauseEvaluators/ClauseEvaluatorCollection.h"

list<string> QueryEvaluator::evaluate(Query* query) {

    auto* optimizer = new QueryOptimizer(query);
    optimizer->groupClauses();
    std::vector<GroupedClause> groupedClauses = optimizer->getClauses();

    unordered_map<int, ResultTable*> groupedResultTables;
    for(const auto& group: *optimizer->getGroups()) {
        groupedResultTables.insert(std::make_pair(group, new ResultTable()));
    }

    bool isFalse = false;

    for (GroupedClause gc : groupedClauses) {
        if (dynamic_cast<WithClause*>(gc.clause)) {
            // Create ClauseEvaluators and evaluate each with clause
            auto* withClause = dynamic_cast<WithClause*>(gc.clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto withClauseEvaluator = new WithClauseEvaluator(query->getDeclarations(), withClause, pkb);
            bool withResult = withClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete withClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!withResult) {
                isFalse = true;
                break;
            }
        }
        else if (dynamic_cast<SuchThatClause*>(gc.clause)){
            // Create ClauseEvaluators and evaluate each suchThat clause
            auto* suchThatClause = dynamic_cast<SuchThatClause *>(gc.clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto suchThatClauseEvaluator = generateEvaluator(*suchThatClause, *query->getDeclarations());
            bool suchThatResult = suchThatClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete suchThatClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation and output an empty list.
            if (!suchThatResult){
                isFalse = true;
                break;
            }
        }
        else if (dynamic_cast<PatternClause*>(gc.clause)){
            // Create ClauseEvaluators and evaluate each pattern clause
            auto* patternClause = dynamic_cast<PatternClause *>(gc.clause);
            //std::cout<< clause->getName() << " group: " << gc.group << std::endl;
            auto patternClauseEvaluator = new PatternClauseEvaluator(query->getDeclarations(), patternClause, pkb);
            bool patternResult = patternClauseEvaluator->evaluateClause(groupedResultTables.at(gc.group));
            delete patternClauseEvaluator;
            // if the clause evaluates to false, terminate evaluation early.
            if (!patternResult) {
                isFalse = true;
                break;
            }
        } else {
            throw qp::QPEvaluatorException("Invalid clause type");
        }
    }

    auto* finalResultTable = new ResultTable();
    mergeToFinalResultTable(finalResultTable, &groupedResultTables, query, isFalse);

    // Evaluate result clause and output the result
    auto* resultClauseEvaluator = new ResultClauseEvaluator(query->getDeclarations(), query->getResultClause(), pkb);
    bool result = resultClauseEvaluator->evaluateClause(finalResultTable);
    delete resultClauseEvaluator;
    if (!result) return {};
    list<string> output = generateResultString(finalResultTable);

    delete finalResultTable;
    for (auto map: groupedResultTables) {
        delete map.second;
    }
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


void QueryEvaluator::mergeToFinalResultTable(ResultTable* finalResultTable, unordered_map<int, ResultTable*>* groupedResultTables, Query* query, bool isFalse) {

    unordered_set<string> selectedSynonyms;
    for (Argument synonym: query->getResultClause()->argList) {
        if (synonym.argumentType == ArgumentType::ATTR_REF) {
            auto attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
            selectedSynonyms.insert(attrRef.first);
        } else if (synonym.argumentType == ArgumentType::SYNONYM) {
            selectedSynonyms.insert(std::get<string>(synonym.argumentValue));
        } else if (synonym.argumentType == ArgumentType::BOOLEAN) {
            finalResultTable->enableBooleanResult();
        }
    }

    if (isFalse) {
        finalResultTable->setBooleanResult(false);
        return;
    }
    if (!selectedSynonyms.empty()) {
        for (auto map: *groupedResultTables) {
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
            if (!selectedColumns.empty())
                finalResultTable->mergeColumnsToTable(selectedColumns, selectedSynonymHeaders);

        }
    }
}
