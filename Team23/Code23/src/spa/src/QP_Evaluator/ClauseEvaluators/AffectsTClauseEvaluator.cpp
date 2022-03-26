//
// Created by Tin Hong Wen on 25/3/22.
//

#include "AffectsTClauseEvaluator.h"

#include "QP_database/AffectsTOperator.h"

bool AffectsTClauseEvaluator::isRelation(string left, string right) {
    return affectsTOperator->computeRelation(left, right);
}

unordered_set<string> AffectsTClauseEvaluator::getLeftSynonymValue(string right) {
    return affectsTOperator->computeLHS(right);
}

unordered_set<string> AffectsTClauseEvaluator::getRightSynonymValue(string left) {
    return affectsTOperator->computeRHS(left);
}

pair<DesignEntity, DesignEntity> AffectsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::ASSIGN, DesignEntity::ASSIGN);
}