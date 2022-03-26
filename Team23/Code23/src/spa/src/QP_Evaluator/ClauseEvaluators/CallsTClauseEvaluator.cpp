//
// Created by Tianyi Wang on 25/3/22.
//

#include "CallsTClauseEvaluator.h"

bool CallsTClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.callsT.isRelationship(left, right);
}

unordered_set<string> CallsTClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.callsT.getLHS(right);
}

unordered_set<string> CallsTClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.callsT.getRHS(left);
}

pair<DesignEntity, DesignEntity> CallsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
}