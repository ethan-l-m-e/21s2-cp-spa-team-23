//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextTClauseEvaluator.h"
#include "TNode/CFG/NodeCFG.h"


//TODO: switch all graph operator to cacheClass
bool NextTClauseEvaluator::isRelation(string left, string right) {
    if(optimisation_activated) {
        return cache->relationship.nextT->isRelationship(left, right);
    } else {
        return nextTOperator->computeRelation(left, right);
    }

}

unordered_set<string> NextTClauseEvaluator::getLeftSynonymValue(string right) {
    if(optimisation_activated) {
        return cache->relationship.nextT->getLHS(right);
    } else {
        return nextTOperator->computeLHS(right);
    }
}

unordered_set<string> NextTClauseEvaluator::getRightSynonymValue(string left) {
    if(optimisation_activated) {
        return cache->relationship.nextT->getRHS(left);
    } else {
        return nextTOperator->computeRHS(left);
    }
}

pair<DesignEntity, DesignEntity> NextTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}