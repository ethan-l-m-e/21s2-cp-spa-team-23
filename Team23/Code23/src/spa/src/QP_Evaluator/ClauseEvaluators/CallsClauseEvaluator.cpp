//
// Created by Tianyi Wang on 25/3/22.
//

#include "CallsClauseEvaluator.h"
bool CallsClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.calls.isRelationship(left, right);
}

unordered_set<string> CallsClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.calls.getLHS(right);
}

unordered_set<string> CallsClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.calls.getRHS(left);
}

pair<DesignEntity, DesignEntity> CallsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
}