//
// Created by Tianyi Wang on 7/2/22.
//

#include "ResultClauseEvaluator.h"
#include "QP_Parser/Exception.h"

bool ResultClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    if (query->getSelectedSynonyms().empty()) throw qp::QPEvaluatorException("No argument was selected");

    // handle select boolean
    if ((query->getSelectedSynonyms())[0].argumentType == ArgumentType::BOOLEAN) {
        resultTable->enableBooleanResult();
        return true;
    }

    // handle select synonym / attribute references
    vector<int> projections;
    if (resultTable->getBooleanResult()) projectSelectedSynonyms(&projections, resultTable);
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
    for (Argument synonym: query->getSelectedSynonyms()) {

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
    Result result = {
            .resultType = ResultType::STRING,
            .resultBoolean =true,
            .resultHeader = synonymValue,
            .resultSet = getAllType(query->getSynonymType(synonymValue))
    };
    resultTable->mergeResultToTable(result);
}

/**
 * Apply attribute reference and populate the header name and caller function for attributes with different value from default.
 * @param attrRef  the attribute reference struct with a string identifier and an attribute name
 * @param func  pointer to the function pointer to be used for getting the mapping of the attribute for each value
 * @param name  pointer to the name of the new header to be added to result table for identifying the attribute column
 * @return  returns a boolean value representing whether name and function pointer have been populated
 */
bool ResultClauseEvaluator::applyAttrRef(std::pair<string, AttrName>& attrRef, std::string (ResultClauseEvaluator::**func)(std::string&), std::string *name) {
    if(query->findEntityType(attrRef.first) == DesignEntity::READ && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ResultClauseEvaluator::getVarRead;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::PRINT && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ResultClauseEvaluator::getVarPrinted;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::CALL && attrRef.second == AttrName::PROC_NAME) {
        *name = attrRef.first + ".procName";
        *func = &ResultClauseEvaluator::getProcByCall;
    } else {
        return false;
    }
    return true;
}

/**
 * Get the mapped new values for the attribute reference from the values in an existing column
 * @param lst  reference to the list in the result table
 * @param func  function pointer indicating the function to be applied for getting the mapped value
 * @return  a new list with the values for the attribute corresponding to each value
 */
std::vector<std::string> ResultClauseEvaluator::getMapping(std::vector<std::string>& lst, std::string (ResultClauseEvaluator::*func) (std::string&)) {
    std::vector<std::string> mappings;
    for (std::string& val: lst) {
        std::string mapped = (this->*func)(val);
        mappings.emplace_back(mapped);
    }
    return mappings;
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
        *synonymValue = std::get<std::string>(synonym.argumentValue);
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
    std::string(ResultClauseEvaluator::*func) (std::string&);
    std::string name;
    if (applyAttrRef(attrRef, &func, &name)) {
        auto it1 = std::find(header->begin(), header->end(), name);
        long newIndex = std::distance(header->begin(), it1);
        if (it1 == header->end()) {
            std::vector<std::string> newColumn = getMapping((*resultTable->getList())[*index], func);
            resultTable->appendColumn(name, newColumn);
        }
        *index = newIndex;
    }
}


string ResultClauseEvaluator::getVarRead(string& stmtNumber) {
    return pkb->statement.readStatements.getVariableName(stmtNumber);
}
string ResultClauseEvaluator::getVarPrinted(string& stmtNumber) {
    return pkb->statement.printStatements.getVariableName(stmtNumber);
}
string ResultClauseEvaluator::getProcByCall(string& stmtNumber) {
    return pkb->statement.callStatements.getProcedureName(stmtNumber);
}