//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsClauseEvaluator.h"

#include "QP_database/AffectsOperator.h"

bool AffectsClauseEvaluator::isRelation(string left, string right) {
    return affectsOperator->computeRelation(left, right);
}

unordered_set<string> AffectsClauseEvaluator::getLeftSynonymValue(string right) {
    return affectsOperator->computeLHS(right);
}

unordered_set<string> AffectsClauseEvaluator::getRightSynonymValue(string left) {
    return affectsOperator->computeRHS(left);
}

pair<DesignEntity, DesignEntity> AffectsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::ASSIGN, DesignEntity::ASSIGN);
}