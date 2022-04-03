//
// Created by Tin Hong Wen on 25/3/22.
//

#include "AffectsTClauseEvaluator.h"

bool AffectsTClauseEvaluator::isRelation(string left, string right) {
    if(optimisation_activated) {
        return cache->relationship.affectsT.isRelationship(left, right);
    } else {
        return affectsTOperator->computeRelation(left, right);
    }
}

// disabled the latter 2 due to unknown issues causing timeout
unordered_set<string> AffectsTClauseEvaluator::getLeftSynonymValue(string right) {
    if(optimisation_activated) {
        return cache->relationship.affectsT.getLHS(right);
    } else {
        return affectsTOperator->computeLHS(right);
    }}

unordered_set<string> AffectsTClauseEvaluator::getRightSynonymValue(string left) {
    if (optimisation_activated){
        return cache->relationship.affectsT.getRHS(left);
    } else {
        return affectsTOperator->computeRHS(left);
    }
}

pair<DesignEntity, DesignEntity> AffectsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::ASSIGN, DesignEntity::ASSIGN);
}