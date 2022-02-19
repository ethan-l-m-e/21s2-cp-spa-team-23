//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

/**
 * Get all values for a given design entity from the pkb
 * @param designEntity  a design entity
 * @return  set of all string identifiers belonging the design entity
 */
unordered_set<std::string> ClauseEvaluator::getAllType(DesignEntity designEntity) {

    switch (designEntity) {
        case DesignEntity::STMT:
            return pkb->getAllStatements();
        case DesignEntity::ASSIGN:
            return pkb->getAllAssignStatements();
        case DesignEntity::READ:
            return pkb->getAllReadStatements();
        case DesignEntity::PRINT:
            return pkb->getAllPrintStatements();
        case DesignEntity::WHILE:
            return pkb->getAllWhileStatements();
        case DesignEntity::IF:
            return pkb->getAllIfStatements();
        case DesignEntity::VARIABLE:
            return pkb->getAllVariables();
        case DesignEntity::CONSTANT:
            return pkb->getAllConstants();
        case DesignEntity::PROCEDURE:
            return pkb->getAllProcedures();
        case DesignEntity::CALL:
            //TODO: To be updated in future iterations
            //return pkb->getAllCalls();
        default:
            return {};
    }
};
