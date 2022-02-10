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

bool ClauseEvaluator::generateTuples(RelRef relRef, unordered_set<std::string> leftSet, unordered_set<std::string> rightSet) {

};
