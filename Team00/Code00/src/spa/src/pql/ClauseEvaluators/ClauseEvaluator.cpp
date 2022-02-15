//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

unordered_set<std::string> ClauseEvaluator::getAllType(DesignEntity designEntity) {

    switch (designEntity) {
        case DesignEntity::VARIABLE:
            return pkb->getAllVariables();
        case DesignEntity::STMT:
            //return pkb->getAllStatement();
        case DesignEntity::ASSIGN:
            //return pkb->getAllAssign();
            //return {"1","2","3","4","5","6"}; //test
        default:
            return {};
    }
};
