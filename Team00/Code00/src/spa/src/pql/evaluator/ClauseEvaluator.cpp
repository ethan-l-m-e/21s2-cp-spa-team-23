//
// Created by リム・イーサン on 31/1/22.
//

#include "ClauseEvaluator.h"

Result ClauseEvaluator::evaluateClause() {
    return Result();
}

bool ClauseEvaluator::hasTwoSynonyms() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType == ArgumentType::SYNONYM && argRight.argumentType == ArgumentType::SYNONYM;
}


bool ClauseEvaluator::hasNoSynonyms() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType != ArgumentType::SYNONYM && argRight.argumentType != ArgumentType::SYNONYM;
}

bool ClauseEvaluator::leftIsSynonym() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType == ArgumentType::SYNONYM;
}

bool ClauseEvaluator::rightIsSynonym() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argRight.argumentType == ArgumentType::SYNONYM;
}

Result ClauseEvaluator::buildResult(ResultType type, ResultHeader header, vector<ResultItem> items) {
    return {type, header, items};
}
