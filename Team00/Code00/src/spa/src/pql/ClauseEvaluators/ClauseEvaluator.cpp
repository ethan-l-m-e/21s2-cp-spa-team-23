//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

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
            //return pkb->getAllCalls();
        default:
            return {};
    }
};
