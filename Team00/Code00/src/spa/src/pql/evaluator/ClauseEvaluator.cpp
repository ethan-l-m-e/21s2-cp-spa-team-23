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

bool ClauseEvaluator::leftIsConcrete() {
    Argument argLeft = argList[0];
    return argLeft.argumentType != ArgumentType::UNDERSCORE && argLeft.argumentType != ArgumentType::SYNONYM;
}

bool ClauseEvaluator::leftIsWildCard() {
    Argument argLeft = argList[0];
    return argLeft.argumentType == ArgumentType::UNDERSCORE;
}

bool ClauseEvaluator::rightIsPartWildCard() {
    Argument argRight = argList[1];
    return argRight.argumentType == ArgumentType::PARTIALUNDERSCORE;
}

bool ClauseEvaluator::rightIsWildCard() {
    Argument argRight = argList[1];
    return argRight.argumentType == ArgumentType::UNDERSCORE;
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

