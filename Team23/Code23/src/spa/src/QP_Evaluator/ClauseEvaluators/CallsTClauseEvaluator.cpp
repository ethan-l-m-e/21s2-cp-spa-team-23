//
// Created by Tianyi Wang on 25/3/22.
//

#include "CallsTClauseEvaluator.h"

bool CallsTClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.callsT.isRelationship(left, right);
}

unordered_set<std::string> CallsTClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.callsT.getLHS(right);
}

unordered_set<std::string> CallsTClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.callsT.getRHS(left);
}

pair<DesignEntity, DesignEntity> CallsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
}