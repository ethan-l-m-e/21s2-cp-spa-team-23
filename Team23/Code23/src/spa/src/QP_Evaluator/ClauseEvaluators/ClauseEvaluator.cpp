//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

#include "QP_Parser/Exception.h"

/**
 * Get all values for a given design entity from the pkb
 * @param designEntity  a design entity
 * @return  set of all string identifiers belonging the design entity
 */
unordered_set<string> ClauseEvaluator::getAllType(DesignEntity designEntity) {

    switch (designEntity) {
        case DesignEntity::STMT:
            return pkb->statement.statements.getAllStatementNumbers();
        case DesignEntity::ASSIGN:
            return pkb->statement.assignStatements.getAllStatementNumbers();
        case DesignEntity::READ:
            return pkb->statement.readStatements.getAllStatementNumbers();
        case DesignEntity::PRINT:
            return pkb->statement.printStatements.getAllStatementNumbers();
        case DesignEntity::WHILE:
            return pkb->statement.whileStatements.getAllStatementNumbers();
        case DesignEntity::IF:
            return pkb->statement.ifStatements.getAllStatementNumbers();
        case DesignEntity::VARIABLE:
            return pkb->entity.variables.getAll();
        case DesignEntity::CONSTANT:
            return pkb->entity.constants.getAll();
        case DesignEntity::PROCEDURE:
            return pkb->entity.procedures.getAll();
        case DesignEntity::CALL:
            return pkb->statement.callStatements.getAllStatementNumbers();
        default:
            throw qp::QPEvaluatorException("Invalid design entity found.");
    }
}

/**
 * Process a result struct and update the result table.
 * @param resultTable  The result table to be updated
 * @return  boolean value to indicate whether the clause has a valid result.
 */
bool ClauseEvaluator::processResult(ResultTable* resultTable) {
    if(!result.resultBoolean) {
        resultTable->clearTable();
        resultTable->setBooleanResult(false);
        return false;
    }
    resultTable->mergeResultToTable(result);
    return resultTable->getBooleanResult();
}

/**
 * Apply attribute reference and populate the header name and caller function for attributes with different value from default.
 * @param attrRef  the attribute reference struct with a string identifier and an attribute name
 * @param func  pointer to the function pointer to be used for getting the mapping of the attribute for each value
 * @param name  pointer to the name of the new header to be added to result table for identifying the attribute column
 * @return  returns a boolean value representing whether name and function pointer have been populated
 */
bool ClauseEvaluator::applyAttrRef(std::pair<string, AttrName>& attrRef, string (ClauseEvaluator::**func)(string&), string *name) {
    if(declarations->at(attrRef.first) == DesignEntity::READ && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ClauseEvaluator::getVarRead;
    } else if (declarations->at(attrRef.first) == DesignEntity::PRINT && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ClauseEvaluator::getVarPrinted;
    } else if (declarations->at(attrRef.first) == DesignEntity::CALL && attrRef.second == AttrName::PROC_NAME) {
        *name = attrRef.first + ".procName";
        *func = &ClauseEvaluator::getProcByCall;
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
vector<string> ClauseEvaluator::getMapping(vector<string>& lst, string (ClauseEvaluator::*func) (string&)) {
    vector<string> mappings;
    for (string& val: lst) {
        string mapped = (this->*func)(val);
        mappings.emplace_back(mapped);
    }
    return mappings;
}

// Helper functions for generating the mapping of key to value by applying a function
unordered_map<string, string> ClauseEvaluator::generateMap(unordered_set<string>& set, string (ClauseEvaluator::*func) (string&)) {
    unordered_map<string, string> mappings;
    for (string val: set) {
        string mapped = (this->*func)(val);
        mappings[val] = mapped;
    }
    return mappings;
}

// Helper functions for generating the mapping of key to value where key = value
unordered_map<string, string> ClauseEvaluator::generateMap(unordered_set<string>& set) {
    unordered_map<string, string> mappings;
    for (string val: set) {
        mappings[val] = val;
    }
    return mappings;
}

/*
 * Wrapper functions for PKB calls
 */
string ClauseEvaluator::getVarRead(string& stmtNumber) {
    return pkb->statement.readStatements.getVariableName(stmtNumber);
}
string ClauseEvaluator::getVarPrinted(string& stmtNumber) {
    return pkb->statement.printStatements.getVariableName(stmtNumber);
}
string ClauseEvaluator::getProcByCall(string& stmtNumber) {
    return pkb->statement.callStatements.getProcedureName(stmtNumber);
}

/*
 * Helper functions for making a result
 */
Result ClauseEvaluator::makeResult(bool validity) {
    return {
            .resultType = ResultType::BOOLEAN,
            .resultBoolean = validity,
    };
}

Result ClauseEvaluator::makeResult(string header, unordered_set<string> values) {
    return {
            .resultType = ResultType::SINGLE,
            .resultBoolean = !values.empty(),
            .resultHeader = header,
            .resultSet = values
    };
}

Result ClauseEvaluator::makeResult(pair<string, string> header, unordered_set<pair<string, string>> values) {
    return {
            .resultType = ResultType::PAIR,
            .resultBoolean = !values.empty(),
            .resultHeader = header,
            .resultSet = values
    };
}


