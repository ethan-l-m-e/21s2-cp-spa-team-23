//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextTClauseEvaluator.h"
#include "TNode/CFG/NodeCFG.h"
#include "QP_database/NextTOperator.h"


//TODO: switch all graph operator to cacheClass
bool NextTClauseEvaluator::isRelation(string left, string right) {
    return nextTOperator->setOptimisation(true)->computeRelation(left, right);
}

unordered_set<string> NextTClauseEvaluator::getLeftSynonymValue(string right) {
    return nextTOperator->computeLHS(right);
}

unordered_set<string> NextTClauseEvaluator::getRightSynonymValue(string left) {
    return nextTOperator->computeRHS(left);
}

pair<DesignEntity, DesignEntity> NextTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}