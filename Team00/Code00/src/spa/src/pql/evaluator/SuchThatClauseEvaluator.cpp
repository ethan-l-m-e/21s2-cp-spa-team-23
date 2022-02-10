//
// Created by Tianyi Wang on 9/2/22.
//

#include "SuchThatClauseEvaluator.h"

bool SuchThatClauseEvaluator::hasTwoSynonyms() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType == ArgumentType::SYNONYM && argRight.argumentType == ArgumentType::SYNONYM;
}


bool SuchThatClauseEvaluator::hasNoSynonym() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType != ArgumentType::SYNONYM && argRight.argumentType != ArgumentType::SYNONYM;
}

bool SuchThatClauseEvaluator::hasLeftSynonym() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argLeft.argumentType == ArgumentType::SYNONYM;
}

bool SuchThatClauseEvaluator::hasRightSynonym() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    return argRight.argumentType == ArgumentType::SYNONYM;
}