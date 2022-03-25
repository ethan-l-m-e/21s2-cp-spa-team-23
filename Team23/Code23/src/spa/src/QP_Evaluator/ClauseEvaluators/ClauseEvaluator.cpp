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

void ClauseEvaluator::mergeResult(ResultTable* resultTable) {
    resultTable->mergeResultToTable(result);
}

