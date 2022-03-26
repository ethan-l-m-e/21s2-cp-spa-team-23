//
// Created by Tianyi Wang on 25/3/22.
//

#include "CallsClauseEvaluator.h"
bool CallsClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.calls.isRelationship(left, right);
}

unordered_set<std::string> CallsClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.calls.getLHS(right);
}

unordered_set<std::string> CallsClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.calls.getRHS(left);
}

pair<DesignEntity, DesignEntity> CallsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
}