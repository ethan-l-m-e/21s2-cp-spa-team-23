//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

Result ClauseEvaluator::evaluateClause() {
    return Result();
}

unordered_set<std::string> ClauseEvaluator::getAllType(DesignEntity designEntity) {
    if (designEntity == DesignEntity::VARIABLE) {
        return pkb->getAllVariables();

    } else {
        return unordered_set<std::string>();
    }
};

Result ClauseEvaluator::buildResult(ResultType type, bool isTrue, ResultHeader header, vector<ResultItem> items) {
    return {type, isTrue, header, items};
}
