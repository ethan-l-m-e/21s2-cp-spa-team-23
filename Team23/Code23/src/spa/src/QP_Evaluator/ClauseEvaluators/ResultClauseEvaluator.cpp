//
// Created by Tianyi Wang on 7/2/22.
//

#include "ResultClauseEvaluator.h"
#include "QP_Parser/Exception.h"

bool ResultClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    if (clause->argList.empty())
        throw qp::QPEvaluatorException("No argument was selected");

    // handle select boolean
    if (resultTable->isBoolean()) return true;

    // handle select synonym / attribute references
    vector<int> projections;
    if (resultTable->getBooleanResult())
        projectSelectedSynonyms(&projections, resultTable);

    resultTable->rearrangeSynonyms(projections);
    return true;

}

/**
 * Project the result by traversing the selected synonyms.
 * @param projections  a vector of integers that represents the column index and order for the final result
 * @param resultTable  pointer to the result table used
 */
void ResultClauseEvaluator::projectSelectedSynonyms(vector<int>* projections, ResultTable* resultTable) {
    auto header = resultTable->getHeader();
    for (Argument synonym: clause->argList) {

        // get synonym value and attribute reference.
        string synonymValue;
        std::pair<string, AttrName> attrRef;
        unpackSynonym(synonym, &attrRef, &synonymValue);
        
        // find synonym in result table.
        auto it = std::find(header->begin(), header->end(), synonymValue);
        auto index = std::distance(header->begin(), it);

        //merge synonyms to result table if synonym is not in the table.
        if (it == header->end()) 
            appendNewSynonym(synonymValue, resultTable);

        //handle attribute reference.
        if (synonym.argumentType == ArgumentType::ATTR_REF) 
            updateTableForAttrReference(attrRef, &index, resultTable);

        projections->emplace_back(index);
    }
}

/**
 * Append a new synonym to the result table by doing a cross product for all the possible values from the synonym.
 * @param synonymValue  the string value of the synonym for identifying the synonym in declarations
 * @param resultTable  pointer to the result table used
 */
void ResultClauseEvaluator::appendNewSynonym(string synonymValue, ResultTable* resultTable){
    Result result = makeResult(synonymValue, getAllType(declarations->at(synonymValue)));
    resultTable->mergeResultToTable(result);
}

/**
 * Unpack the synonym argument and assign to an AttrRef struct and the string identifier of the synonym
 * @param synonym  synonym argument to be unpacked
 * @param attrRef  pointer to the AttrRef
 * @param synonymValue  pointer to the string identifier of the synonym
 */
void ResultClauseEvaluator::unpackSynonym(Argument &synonym, std::pair<string, AttrName> *attrRef, string *synonymValue) {
    if (synonym.argumentType == ArgumentType::ATTR_REF) {
        *attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
        *synonymValue = attrRef->first;
    } else if (synonym.argumentType == ArgumentType::SYNONYM) {
        *synonymValue = std::get<string>(synonym.argumentValue);
    } else {
        throw qp::QPEvaluatorException("Invalid selected argument type");
    }
}

/**
 * Handle selection the attribute reference, update result table and index if needed
 * @param attrRef  Attribute Reference of a synonym
 * @param index  pointer originally storing the position for the current synonym, updated if new column is added
 * @param resultTable  pointer to the result table to be used
 */
void ResultClauseEvaluator::updateTableForAttrReference(std::pair<string, AttrName> &attrRef, long* index, ResultTable* resultTable) {
    auto header = resultTable->getHeader();
    string(ClauseEvaluator::*func) (string&);
    string name;
    if (applyAttrRef(attrRef, &func, &name)) {
        auto it1 = std::find(header->begin(), header->end(), name);
        long newIndex = std::distance(header->begin(), it1);
        if (it1 == header->end()) {
            vector<string> newColumn = getMapping((*resultTable->getList())[*index], func);
            resultTable->appendColumn(name, newColumn);
        }
        *index = newIndex;
    }
}
