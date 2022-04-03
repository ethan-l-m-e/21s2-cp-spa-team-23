//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsClauseEvaluator.h"

bool AffectsClauseEvaluator::isRelation(string left, string right) {
    if(optimisation_activated) {
        return cache->relationship.affects->isRelationship(left, right);
    } else {
        return affectsOperator->computeRelation(left, right);
    }
}

unordered_set<string> AffectsClauseEvaluator::getLeftSynonymValue(string right) {
    if(optimisation_activated) {
        return cache->relationship.affects->getLHS(right);
    } else {
        return affectsOperator->computeLHS(right);
    }

}

unordered_set<string> AffectsClauseEvaluator::getRightSynonymValue(string left) {
    if (optimisation_activated){
        return cache->relationship.affects->getRHS(left);
    } else {
        return affectsOperator->computeRHS(left);
    }
}

pair<DesignEntity, DesignEntity> AffectsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::ASSIGN, DesignEntity::ASSIGN);
}