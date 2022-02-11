//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

unordered_set<std::string> ClauseEvaluator::getAllType(DesignEntity designEntity) {
    if (designEntity == DesignEntity::VARIABLE) {
        return pkb->getAllVariables();

    } else {
        return unordered_set<std::string>();
    }
};
